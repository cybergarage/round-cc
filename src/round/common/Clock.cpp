/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Clock.h>

Round::Clock::Clock() {
setValue(0);
}

Round::Clock::Clock(ClockValue value) {
setValue(value);
}

Round::Clock::~Clock() {}

Round::ClockOrderType Round::Clock::compare(const Clock &clock) {
  if (this->value == clock.getValue())
    return ClockOrderedSame;
  return (clock.getValue() < this->value) ? ClockOrderedDescending : ClockOrderedAscending;
}
