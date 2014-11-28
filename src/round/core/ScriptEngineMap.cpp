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

Round::ScriptEngineMap::ScriptEngineMap() {
}

Round::ScriptEngineMap::~ScriptEngineMap() {
  clear();
}

bool Round::ScriptEngineMap::hasEngine(const ScriptLang &lang) const {
  return (find(lang) != end()) ? true : false;
}

const Round::ScriptEngine *Round::ScriptEngineMap::getEngine(const ScriptLang &lang) const {
  ScriptEngineMap::const_iterator engineIt = find(lang);
  if (engineIt == end())
    return NULL;
  return engineIt->second;
}

void Round::ScriptEngineMap::clear() {
  for (ScriptEngineMap::iterator engineIt = begin(); engineIt != end(); engineIt++) {
    ScriptEngine *script = engineIt->second;
    if (script)
      delete script;
  }
  
  std::map<std::string, ScriptEngine *>::clear();
}
