/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <sstream>

#include <round/common/Message.h>

static const std::string FRACTAL_MESSAGE_CLOCK_KEY = "_msg_colck_";

Round::Message::Message() {}

Round::Message::~Message() {}

void Round::Message::setClock(const Clock &clock) {
  std::stringstream ss;
  ss << clock.getValue();
  set(FRACTAL_MESSAGE_CLOCK_KEY, ss.str());
}

bool Round::Message::hasClock() const {
  return hasKey(FRACTAL_MESSAGE_CLOCK_KEY);
}

bool Round::Message::getClock(Clock *clock) const {
  std::string clockString;
  if (get(FRACTAL_MESSAGE_CLOCK_KEY, &clockString) == false)
    return false;

  if (clockString.length() <= 0)
    return false;
  
  std::istringstream iss(clockString);
  ClockValue clockValue;
  iss >> clockValue;
  clock->setValue(clockValue);

  return true;
}
