/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sys/time.h>
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
  long    second;
  int     milisecond;
  
  struct timeval  time;
  struct timezone timeZone;
  gettimeofday(&time, &timeZone);
  
  second = time.tv_sec;
  milisecond = time.tv_usec / 1000;
  
  return ((double)second + ((double)milisecond / 1000.0));
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

bool Round::TimerTrigger::update() {
  LocalNode *node = dynamic_cast<LocalNode *>(getNode());
  if (!node)
    return false;
  
  double currTime = getCurrentTime();
  
  if (this->lastExecutedTime < 0) {
    if (!node->execTrigger(this->name))
      return false;
    this->lastExecutedTime = currTime;
    return true;
  }

  if ((this->lastExecutedTime + this->duration) < currTime) {
    if (!node->execTrigger(this->name))
      return false;
    this->lastExecutedTime = currTime;
    return true;
  }

  return false;
}
