/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Trigger.h>

Round::TriggerMap::TriggerMap() {
}

Round::TriggerMap::~TriggerMap() {
  clear();
}

void Round::TriggerMap::clear() {
  for (TriggerMap::iterator aliasIt = begin(); aliasIt != end(); aliasIt++) {
    Trigger *alias = aliasIt->second;
    if (alias) {
      delete alias;
    }
  }
  std::map<std::string, Trigger*>::clear();
}

bool Round::TriggerMap::hasTrigger(const std::string &name) const {
  return (find(name) != end()) ? true  : false;
}

Round::Trigger *Round::TriggerMap::findTrigger(const std::string &name) const {
  TriggerMap::const_iterator valueIt = find(name);
  if (valueIt == end())
    return NULL;
  return valueIt->second;
}

bool Round::TriggerMap::getSourceObjects(const std::string &name, std::string *object) const {
  Trigger *alias = findTrigger(name);
  if (!alias)
    return NULL;
  return alias->getObject(object);
}

bool Round::TriggerMap::addTrigger(Trigger *alias) {
  std::string name;
  if (!alias->getName(&name))
    return false;
  
  if (hasTrigger(name))
    return false;
  
  insert(std::pair<std::string, Trigger *>(name, alias));

  return true;
}

bool Round::TriggerMap::setTrigger(Trigger *alias) {
  std::string name;
  if (!alias->getName(&name))
    return false;

  if (hasTrigger(name)) {
    if (!removeTriggerByName(name))
      return false;
  }
  
  return addTrigger(alias);
}

bool Round::TriggerMap::removeTriggerByName(const std::string &name) {
  return (0 < erase(name)) ? true : false;
}
