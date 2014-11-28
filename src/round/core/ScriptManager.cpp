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

bool Round::ScriptManager::run(const ScriptName &name, const ScriptParams &params, ScriptResults *results, Error *error) {
  error->setCode(ScriptEngineStatusOk);
  error->setDetailCode(ScriptManagerDetailStatusOk);
  
  const Script *script = this->scripts.getScript(name);
  if (!script) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setDetailCode(ScriptManagerDetailStatusMethodNotFound);
    return false;
  }
  
  const ScriptLang &scriptLang = script->getLanguage();
  if (scriptLang.length() <= 0) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setDetailCode(ScriptManagerDetailStatusScriptEngineNotFound);
    return false;
  }
  
  const ScriptEngine *scriptEngine = this->engines.getEngine(scriptLang);
  if (!scriptEngine) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setDetailCode(ScriptManagerDetailStatusScriptEngineNotFound);
    return false;
  }
  
  return scriptEngine->run(script, params, results, error);
}

