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

#include <round/common/encoding/Base64.h>
#include <round/core/Log.h>
#include <round/script/Tcl.h>

#if defined(ROUND_SUPPORT_TCL)

const std::string Round::TclEngine::LANGUAGE = "tcl";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::TclEngine::TclEngine() : ScriptEngine(LANGUAGE) {
  /*
  this->interp = Tcl_CreateInterp();
   */
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Round::TclEngine::~TclEngine() {
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Round::TclEngine::compile(const Script *script) const {
  if (!script)
    return false;
  
  std::string jsSource = script->getStringCode();
  std::string results;
  Error error;
  
  return run(jsSource, &results, &error);
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::TclEngine::run(const Script *tclScript, const std::string &params, std::string *results, Error *error) const {
  std::stringstream tclSource;
  
  tclSource << tclScript->getCode() << std::endl;
  
  std::string jsonParams = boost::algorithm::replace_all_copy(params, "\"", "\\\"");
  
  tclSource << "set params = \"" << jsonParams << "\";" << std::endl;
  tclSource << "set results = " << tclScript->getName() << "(params);" << std::endl;
  tclSource << "results;";
  
  return run(tclSource.str(), results, error);
}

bool Round::TclEngine::run(const std::string &jsSource, std::string *results, Error *error) const {
  /*
  int isSuccess = Tcl_Eval(tcl_interp, jsSource.c_str()) ;
  return (isSuccess == TCL_OK) ? true : false;
   */
  return true;
}

#endif
