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
  init();
}

Round::TimerTrigger::TimerTrigger(const std::string &name, time_t duration, bool loop) {
  init();
  setName(name);
  setDuration(duration);
  setLoop(loop);
}

Round::TimerTrigger::~TimerTrigger() {
}

bool Round::TimerTrigger::init() {
  this->lastExecutedTime = -1;
  
  setDuration(0);
  setLoop(false);
  
  return true;
}

double Round::TimerTrigger::getCurrentTime() {
  return 0;
}

bool Round::TimerTrigger::setDuration(double value) {
  this->duration = value;
  return true;
}

double Round::TimerTrigger::getDuration() const {
  return this->duration;
}

bool Round::TimerTrigger::setLoop(bool value) {
  this->loop = value;
  return true;
}

bool Round::TimerTrigger::isLoop() const {
  return this->loop;
}

void Round::TimerTrigger::run() {
  LocalNode *node = dynamic_cast<LocalNode*>(getObject());
  if (!node)
    return;
}

bool Round::TimerTrigger::update() {
  double currTime = getCurrentTime();
  
  if (this->lastExecutedTime < 0) {
    this->lastExecutedTime = currTime;
    return true;
  }

  if ((this->lastExecutedTime + this->duration) < currTime) {
    this->lastExecutedTime = currTime;
    return true;
  }

  return false;
}
