/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Script.h>

Round::ScriptManager::ScriptManager() {
  setNode(NULL);
}

Round::ScriptManager::~ScriptManager() {
}

bool Round::ScriptManager::setScript(Script *script) {
  if (!script)
    return false;
  
  const std::string &name = script->getName();
  if (name.length() <= 0) {
    return false;
  }

  const Script *currentScript = this->scripts.getScript(name);
  if (currentScript) {
    delete currentScript;
  }
  
  this->scripts[name] = script;
  script->setNode(hasNode() ? getNode() : NULL);
  
  return true;
}

bool Round::ScriptManager::setEngine(ScriptEngine *engine) {
  if (!engine)
    return false;
  
  const std::string &engineLang = engine->getLanguage();
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

bool Round::ScriptManager::setScript(const std::string &method, const std::string &lang, const std::string &code, int encodeType, Error *error) {
  const ScriptEngine *scriptEngine = this->engines.getEngine(lang);
  if (!scriptEngine) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineNotFound, error);
    return false;
  }

  if (code.length() <= 0)
    return removeScript(method, lang, error);
  
  Script *script = new Script(lang, method, code);
  if (!script) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineInternalError, error);
    return false;
  }
  script->setEncording(encodeType);
  
  if (!scriptEngine->compile(script)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptCompileError, error);
    delete script;
    return false;
  }
  
  if (!setScript(script)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineInternalError, error);
    delete script;
    return false;
  }
  
  return true;
}

bool Round::ScriptManager::removeScript(const std::string &method, const std::string &lang, Error *error) {
  const Script *script = this->scripts.getScript(method);
  if (!script) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  if (!script->isLanguage(lang)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  return (this->scripts.erase(method) == 1) ? true : false;
}

bool Round::ScriptManager::execScript(const std::string &lang, const std::string &script, int encodeType, std::string *result, Error *error) {
  const ScriptEngine *scriptEngine = this->engines.getEngine(lang);
  if (!scriptEngine) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineInternalError, error);
    return false;
  }
  
  return scriptEngine->run(script, result, error);
}

bool Round::ScriptManager::execMethod(const std::string &name, const std::string &params, std::string *results, Error *error) {
  error->setCode(ScriptEngineStatusOk);
  
  const Script *script = this->scripts.getScript(name);
  if (!script) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  const std::string &scriptLang = script->getLanguage();
  if (scriptLang.length() <= 0) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineNotFound, error);
    return false;
  }
  
  const ScriptEngine *scriptEngine = this->engines.getEngine(scriptLang);
  if (!scriptEngine) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeScriptEngineInternalError, error);
    return false;
  }
  
  return scriptEngine->run(script, params, results, error);
}

bool Round::ScriptManager::toJSONArray(JSONArray *jsonArray, Error *error) {
  this->scripts.toJSONArray(jsonArray);
  return true;
}

