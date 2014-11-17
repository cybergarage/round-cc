/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <time.h>
#include <round/common/Clock.h>

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
