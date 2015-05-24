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

BOOST_AUTO_TEST_CASE(TriggerMapTest) {
  const std::string TEST_NAME = "tname";
  
  TriggerMap triggerMap;
  Trigger *trigger;
  
  // initialize node
  
  BOOST_CHECK_EQUAL(triggerMap.size(), 0);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), false);
  
  // addTrigger
  
  trigger = new TimerTrigger();
  BOOST_CHECK_EQUAL(trigger->setName(TEST_NAME), true);
  
  BOOST_CHECK_EQUAL(triggerMap.addTrigger(trigger), true);
  BOOST_CHECK_EQUAL(triggerMap.size(), 1);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), true);
  
  BOOST_CHECK_EQUAL(triggerMap.addTrigger(trigger), false);
  BOOST_CHECK_EQUAL(triggerMap.size(), 1);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), true);
  
  // setTrigger
  
  trigger = new TimerTrigger();
  BOOST_CHECK_EQUAL(trigger->setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), true);
  
  BOOST_CHECK_EQUAL(triggerMap.setTrigger(trigger), true);
  BOOST_CHECK_EQUAL(triggerMap.size(), 1);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), true);
  
  // findTrigger
  
  Trigger *foundTrigger = triggerMap.findTrigger(TEST_NAME);
  BOOST_CHECK(foundTrigger);
  BOOST_CHECK_EQUAL(foundTrigger->equals(trigger), true);
  
  // removeTrigger
  
  BOOST_CHECK_EQUAL(triggerMap.removeTriggerByName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(triggerMap.size(), 0);
  BOOST_CHECK_EQUAL(triggerMap.hasTrigger(TEST_NAME), false);
}

BOOST_AUTO_TEST_SUITE_END()
