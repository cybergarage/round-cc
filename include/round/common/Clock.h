/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_CLOCK_H_
#define _FRACTALCC_CLOCK_H_

namespace Round {

typedef enum {
ClockOrderedSame = 0,
ClockOrderedDescending = -1,
ClockOrderedAscending = 1,
} ClockOrderType;

typedef long ClockValue;

class Clock {
 public:
  Clock();
  Clock(ClockValue value);

  ~Clock();

  void setValue(ClockValue value) {
    this->value = value;
  }

  ClockValue getValue() const {
    return this->value;
  }

  ClockOrderType compare(const Clock &clock);

private:

  long value;
};

}

#endif
