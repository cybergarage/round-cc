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
  for (TriggerMap::iterator triggerIt = begin(); triggerIt != end(); triggerIt++) {
    Trigger *trigger = triggerIt->second;
    if (trigger) {
      delete trigger;
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

bool Round::TriggerMap::addTrigger(Trigger *trigger) {
  std::string name;
  if (!trigger->getName(&name))
    return false;
  
  if (hasTrigger(name))
    return false;
  
  insert(std::pair<std::string, Trigger *>(name, trigger));

  return true;
}

bool Round::TriggerMap::setTrigger(Trigger *trigger) {
  std::string name;
  if (!trigger->getName(&name))
    return false;

  if (hasTrigger(name)) {
    if (!removeTriggerByName(name))
      return false;
  }
  
  return addTrigger(trigger);
}

bool Round::TriggerMap::removeTriggerByName(const std::string &name) {
  return (0 < erase(name)) ? true : false;
}
