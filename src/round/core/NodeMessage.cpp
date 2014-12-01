/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>

#include <round/core/NodeMessage.h>

const std::string Round::NodeMessage::KEY_CLOCK = "_clock";

Round::NodeMessage::NodeMessage() {
}

Round::NodeMessage::~NodeMessage() {
}

void Round::NodeMessage::setClock(const Clock &clock) {
  std::stringstream ss;
  ss << clock.getValue();
  set(KEY_CLOCK, ss.str());
}

bool Round::NodeMessage::hasClock() const {
  return hasKey(KEY_CLOCK);
}

bool Round::NodeMessage::getClock(Clock *clock) const {
  std::string clockString;
  if (get(KEY_CLOCK, &clockString) == false)
    return false;
  
  if (clockString.length() <= 0)
    return false;
  
  std::istringstream iss(clockString);
  ClockValue clockValue;
  iss >> clockValue;
  clock->setValue(clockValue);
  
  return true;
}
