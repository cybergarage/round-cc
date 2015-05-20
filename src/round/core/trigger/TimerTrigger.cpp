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
#include <round/core/LocalNode.h>

Round::TimerTrigger::TimerTrigger() {
}

Round::TimerTrigger::~TimerTrigger() {
}

void Round::TimerTrigger::run() {
  LocalNode *node = dynamic_cast<LocalNode*>(getObject());
  if (!node)
    return;
}
