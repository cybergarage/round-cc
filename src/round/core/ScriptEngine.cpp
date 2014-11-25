/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Script.h>

Round::ScriptEngine::ScriptEngine() {
}

Round::ScriptEngine::~ScriptEngine() {
}

bool Round::ScriptEngine::setScript(Script *script) {
  if (!script)
    return false;
  if (!script->hasName())
    return false;
  this->scripts[script->getName()] = script;
  return true;
}

bool Round::ScriptEngine::run(const std::string &name, const std::string &params, std::string *results, Error *error) {
  error->setCode(ScriptEngineStatusOk);
  error->setDetailCode(ScriptEngineDetailStatusOk);

  Script *script = this->scripts.getScript(name);
  if (!script) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setDetailCode(ScriptEngineDetailStatusMethodNotFound);
    return false;
  }
  
  return run(script, params, results, error);
}
