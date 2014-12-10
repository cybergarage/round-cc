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

Round::ScriptManager::ScriptManager() {
}

Round::ScriptManager::~ScriptManager() {
}

bool Round::ScriptManager::setScript(Script *script) {
  if (!script)
    return false;
  
  const ScriptName &name = script->getName();
  if (name.length() <= 0) {
    return false;
  }
  
  const Script *currentScript = this->scripts.getScript(name);
  if (currentScript) {
    delete currentScript;
  }
  
  this->scripts[name] = script;
  
  return true;
}

bool Round::ScriptManager::setEngine(ScriptEngine *engine) {
  if (!engine)
    return false;
  
  const ScriptLang &engineLang = engine->getLanguage();
  if (engineLang.length() <= 0) {
    return false;
  }
  
  const ScriptEngine *currentEngine = this->engines.getEngine(engineLang);
  if (currentEngine) {
    delete currentEngine;
  }
  
  this->engines[engineLang] = engine;

  return true;
}

bool Round::ScriptManager::setScript(const ScriptName &method, const ScriptLang &lang, const ScriptCode &code, Error *error) {
  const ScriptEngine *scriptEngine = this->engines.getEngine(lang);
  if (!scriptEngine) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeScriptEngineNotFound, error);
    return false;
  }

  if (code.length() <= 0)
    return removeScript(method, lang, error);
  
  Script *script = new Script(lang, method, code);
  if (!script) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeScriptEngineInternalError, error);
    return false;
  }

  if (!scriptEngine->compile(script)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeCompileError, error);
    delete script;
    return false;
  }
  
  if (!setScript(script)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeScriptEngineInternalError, error);
    delete script;
    return false;
  }
  
  return true;
}

bool Round::ScriptManager::removeScript(const ScriptName &method, const ScriptLang &lang, Error *error) {
  const Script *script = this->scripts.getScript(method);
  if (!script) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, error);
    return false;
  }
  
  if (!script->isLanguage(lang)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, error);
    return false;
  }
  
  return (this->scripts.erase(method) == 1) ? true : false;
}

bool Round::ScriptManager::run(const ScriptName &name, const ScriptParams &params, ScriptResults *results, Error *error) {
  error->setCode(ScriptEngineStatusOk);
  error->setDetailCode(ScriptManagerErrorCodeOk);
  
  const Script *script = this->scripts.getScript(name);
  if (!script) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, error);
    return false;
  }
  
  const ScriptLang &scriptLang = script->getLanguage();
  if (scriptLang.length() <= 0) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeScriptEngineNotFound, error);
    return false;
  }
  
  const ScriptEngine *scriptEngine = this->engines.getEngine(scriptLang);
  if (!scriptEngine) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeScriptEngineInternalError, error);
    return false;
  }
  
  return scriptEngine->run(script, params, results, error);
}

