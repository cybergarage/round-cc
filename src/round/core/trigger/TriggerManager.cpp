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
    sleep(1);
  }
}
