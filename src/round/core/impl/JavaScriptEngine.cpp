/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

#include <round/core/impl/JavaScript.h>

const std::string Round::JavaScriptEngine::LANGUAGE = "js";

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

Round::JavaScriptEngine::JavaScriptEngine() : ScriptEngine(LANGUAGE) {
  init();
}

Round::JavaScriptEngine::~JavaScriptEngine() {
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////

bool Round::JavaScriptEngine::getSourceCode(const Script *jsScript, const std::string &params, std::string *sourceCode) const {
  std::stringstream jsSource;
  
  jsSource << jsScript->getCode() << std::endl;
  
  std::string jsonParams = boost::algorithm::replace_all_copy(params, "\"", "\\\"");
  
  jsSource << "var jsonParams = \"" << jsonParams << "\";" << std::endl;
  jsSource << "var params = JSON.parse(jsonParams);" << std::endl;
  
  jsSource << "var results = " << jsScript->getName() << "(params);" << std::endl;
  jsSource << "var jsonResults = JSON.stringify(results);" << std::endl;
  jsSource << "jsonResults;";

  *sourceCode = jsSource.str();

  return true;
}

bool Round::JavaScriptEngine::compile(const Script *script) const {
  if (!script)
    return false;
  
  std::string jsSource = script->getStringCode();
  std::string results;
  Error error;
  
  return run(jsSource, &results, &error);
}

bool Round::JavaScriptEngine::run(const Script *jsScript, const std::string &params, std::string *results, Error *error) const {
  std::string jsSource;
  
  if (!getSourceCode(jsScript, params, &jsSource)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    return false;
  }
  
  return run(jsSource, results, error);
}
