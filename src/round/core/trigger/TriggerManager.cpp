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

#include <string.h>

Round::TriggerManager::TriggerManager() {
}

Round::TriggerManager::~TriggerManager() {
  stop();
}

bool Round::TriggerManager::start() {
  for (TriggerMap::iterator triggerIt = begin(); triggerIt != end(); triggerIt++) {
    Trigger *trigger = triggerIt->second;
    trigger->start();
  }
  return true;
}

bool Round::TriggerManager::stop() {
  for (TriggerMap::iterator triggerIt = begin(); triggerIt != end(); triggerIt++) {
    Trigger *trigger = triggerIt->second;
    trigger->stop();
  }
  return true;
}
