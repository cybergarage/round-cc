/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_CLOCK_H_
#define _ROUNDCC_CLOCK_H_

#include <time.h>
#include <round/common/Mutex.h>

namespace Round {

typedef enum {
ClockOrderedSame = 0,
ClockOrderedDescending = -1,
ClockOrderedAscending = 1,
} ClockOrderType;

class Clock {
 public:
  const static clock_t INCREMENT_VALUE;
  
 public:
  Clock();
  Clock(clock_t value);

  ~Clock();

  void setValue(clock_t value);
  clock_t getValue() const;
  clock_t increment();

  ClockOrderType compare(const Clock &clock);

private:

  mutable Mutex mutex;
  clock_t value;
};

}

#endif
