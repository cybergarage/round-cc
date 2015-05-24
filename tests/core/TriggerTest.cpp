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

#include <round/core/Trigger.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(trigger)

BOOST_AUTO_TEST_CASE(TimerTriggerTest) {
  TimerTrigger trigger;
  
  const time_t TEST_DURATION = 1234;
  BOOST_CHECK_EQUAL(trigger.getDuration(), 0);
  BOOST_CHECK(trigger.setDuration(TEST_DURATION));
  BOOST_CHECK_EQUAL(trigger.getDuration(), TEST_DURATION);

  BOOST_CHECK_EQUAL(trigger.isLoop(), false);
  BOOST_CHECK(trigger.setLoop(true));
  BOOST_CHECK_EQUAL(trigger.isLoop(), true);
  BOOST_CHECK(trigger.setLoop(false));
  BOOST_CHECK_EQUAL(trigger.isLoop(), false);
}

BOOST_AUTO_TEST_CASE(TriggerTest) {
}

BOOST_AUTO_TEST_SUITE_END()
