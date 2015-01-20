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

Round::ScriptMap::ScriptMap() {
}

Round::ScriptMap::~ScriptMap() {
  clear();
}

bool Round::ScriptMap::hasScript(const std::string &name) const {
  return (find(name) != end()) ? true : false;
}

const Round::Script *Round::ScriptMap::getScript(const std::string &name) const {
  ScriptMap::const_iterator scriptIt = find(name);
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
