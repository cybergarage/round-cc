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

Round::ScriptMap::ScriptMap() {
}

Round::ScriptMap::~ScriptMap() {
  clear();
}

bool Round::ScriptMap::hasScript(const ScriptName &name) {
  return (find(name) != end()) ? true : false;
}

Round::Script *Round::ScriptMap::getScript(const ScriptName &name) {
  ScriptMap::iterator scriptIt = find(name);
  if (scriptIt == end())
    return NULL;
  return scriptIt->second;
}

void Round::ScriptMap::clear() {
  for (ScriptMap::iterator scriptIt = begin(); scriptIt != end(); scriptIt++) {
    Script *script = scriptIt->second;
    if (script)
      delete script;
  }
  
  std::map<std::string, Script *>::clear();
}
