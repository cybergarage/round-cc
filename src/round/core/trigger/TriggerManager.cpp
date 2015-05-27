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

double Round::TriggerManager::DEFAULT_CYCLE_TIME = ROUNDCC_SYSTEM_TRIGGER_TIMER_PRECISION;

Round::TriggerManager::TriggerManager() {
  setCycleTime(DEFAULT_CYCLE_TIME);
}

Round::TriggerManager::~TriggerManager() {
}

bool Round::TriggerManager::start() {
  Node *node = dynamic_cast<Node *>(getObject());
  for (TriggerMap::iterator triggerIt = begin(); triggerIt != end(); triggerIt++) {
    Trigger *trigger = triggerIt->second;
    trigger->setNode(node);
  }
  return Thread<Node>::start();
}

void Round::TriggerManager::run() {
  while (isRunnable() == true) {
    for (TriggerMap::iterator triggerIt = begin(); triggerIt != end(); triggerIt++) {
      Trigger *trigger = triggerIt->second;
      trigger->update();
    }
    
    long execCycleTime = this->cycleTime * 1000.0;
    sleep(execCycleTime);
  }
}
