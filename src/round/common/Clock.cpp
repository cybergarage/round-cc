/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Clock.h>

const clock_t Round::Clock::INCREMENT_VALUE = 1;

Round::Clock::Clock() {
  setValue(0);
}

Round::Clock::Clock(clock_t value) {
  setValue(value);
}

Round::Clock::~Clock() {
}

void Round::Clock::setValue(clock_t value) {
  this->mutex.lock();
  this->value = value;
  this->mutex.unlock();
}

clock_t Round::Clock::getValue() const {
  this->mutex.lock();
  clock_t currValue = this->value;
  this->mutex.unlock();
  return currValue;
}

clock_t Round::Clock::increment() {
  this->mutex.lock();
  this->value += INCREMENT_VALUE;
  this->mutex.unlock();
  return getValue();
}

Round::ClockOrderType Round::Clock::compare(const Clock &clock) {
  if (this->value == clock.getValue())
    return ClockOrderedSame;
  return (clock.getValue() < this->value) ? ClockOrderedDescending : ClockOrderedAscending;
}
