/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/common/Clock.h>

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(ClockTest) {
  Round::Clock clock;
  
  time_t timeValue = time(NULL);
  clock.setValue(timeValue);
  BOOST_CHECK_EQUAL(clock.getValue(), timeValue);
}

BOOST_AUTO_TEST_CASE(ClockConstructorTest) {
  time_t timeValue = time(NULL);
  Round::Clock clock(timeValue);
  BOOST_CHECK_EQUAL(clock.getValue(), timeValue);
}

BOOST_AUTO_TEST_CASE(ClockIncrementTest) {
  time_t timeValue = time(NULL);
  
  Round::Clock clock(timeValue);

  clock_t startClock = clock.getValue();
  
  const int incLoopCnt = 10;
  for (int n=0; n<incLoopCnt; n++) {
    clock_t prevClock = clock.getValue();
    clock_t nowClock = clock.increment();
    BOOST_CHECK(prevClock < nowClock);
    BOOST_CHECK_EQUAL(nowClock, (prevClock + Round::Clock::INCREMENT_VALUE));
  }
  
  clock_t endClock = clock.getValue();
  BOOST_CHECK_EQUAL(endClock, (startClock + incLoopCnt));
}

BOOST_AUTO_TEST_CASE(ClockCompareTest) {
  time_t timeValue = time(NULL);

  Round::Clock clock01(timeValue);
  Round::Clock clock02(timeValue);
  Round::Clock clock03(timeValue + 1);
  Round::Clock clock04(timeValue - 1);

  BOOST_CHECK_EQUAL(clock01.compare(clock01), Round::ClockOrderedSame);
  BOOST_CHECK_EQUAL(clock01.compare(clock02), Round::ClockOrderedSame);
  BOOST_CHECK_EQUAL(clock01.compare(clock03), Round::ClockOrderedAscending);
  BOOST_CHECK_EQUAL(clock01.compare(clock04), Round::ClockOrderedDescending);
}

BOOST_AUTO_TEST_SUITE_END()

