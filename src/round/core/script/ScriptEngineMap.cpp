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

Round::ScriptEngineMap::ScriptEngineMap() {
  init();
}

Round::ScriptEngineMap::~ScriptEngineMap() {
  clear();
}

void Round::ScriptEngineMap::init() {
}

bool Round::ScriptEngineMap::hasEngine(const std::string &lang) const {
  return (find(lang) != end()) ? true : false;
}

const Round::ScriptEngine *Round::ScriptEngineMap::getEngine(const std::string &lang) const {
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
