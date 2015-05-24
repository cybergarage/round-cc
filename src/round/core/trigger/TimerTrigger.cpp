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
  this->lastExecutedTime = 0;
  
  setDuration(0);
  setLoop(false);
  
  return true;
}

bool Round::TimerTrigger::setDuration(time_t value) {
  this->duration = value;
  return true;
}

time_t Round::TimerTrigger::getDuration() const {
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
/*
  double startTime = getStartTime();
  double stopTime = getStopTime();
  double cycleInterval = getCycleInterval();
  
  bool bActive	= isActive();
  bool bEnable	= isEnabled();
  bool bLoop		= isLoop();
  
  if (currentTime == 0)
    currentTime = GetCurrentSystemTime();
  
  // isActive
  if (bEnable == false && bActive == true) {
    setIsActive(false);
    sendEvent(getIsActiveField());
    return;
  }
  
  if (bActive == false && bEnable == true) {
    if (startTime <= currentTime) {
      if (bLoop == true && stopTime <= startTime)
        bActive = true;
      else if (bLoop == false && stopTime <= startTime)
        bActive = true;
      else if (currentTime <= stopTime) {
        if (bLoop == true && startTime < stopTime)
          bActive = true;
        else if	(bLoop == false && startTime < (startTime + cycleInterval) && (startTime + cycleInterval) <= stopTime)
          bActive = true;
        else if (bLoop == false && startTime < stopTime && stopTime < (startTime + cycleInterval))
          bActive = true;
      }
    }
    if (bActive) {
      setIsActive(true);
      sendEvent(getIsActiveField());
      setCycleTime(currentTime);
      sendEvent(getCycleTimeField());
    }
  }
  
  currentTime = GetCurrentSystemTime();
  
  if (bActive == true && bEnable == true) {
    if (bLoop == true && startTime < stopTime) {
      if (stopTime < currentTime)
        bActive = false;
    }
    else if (bLoop == false && stopTime <= startTime) {
      if (startTime + cycleInterval < currentTime)
        bActive = false;
    }
    else if (bLoop == false && startTime < (startTime + cycleInterval) && (startTime + cycleInterval) <= stopTime) {
      if (startTime + cycleInterval < currentTime)
        bActive = false;
    }
    else if (bLoop == false && startTime < stopTime && stopTime < (startTime + cycleInterval)) {
      if (stopTime < currentTime)
        bActive = false;
    }
    
    if (bActive == false) {
      setIsActive(false);
      sendEvent(getIsActiveField());
    }
  }
  
  if (bEnable == false || isActive() == false)
    return;
  
  // fraction_changed
  double	fraction = fmod(currentTime - startTime, cycleInterval);
  if (fraction == 0.0 && startTime < currentTime)
    fraction = 1.0;
  else
    fraction /= cycleInterval;
  setFractionChanged((float)fraction);
  sendEvent(getFractionChangedField());
  
  // cycleTime
  double	cycleTime		= getCycleTime();
  double	cycleEndTime	= cycleTime + cycleInterval;
  while (cycleEndTime < currentTime) {
    setCycleTime(cycleEndTime);
    cycleEndTime += cycleInterval;
    setCycleTime(currentTime);
    sendEvent(getCycleTimeField());
  }
  
  // time
  setTime(currentTime);
  sendEvent(getTimeField());
*/
  return false;
}
