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

#include "TestFinder.h"
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(RoundNodeFinderStartAndStopTest) {
  Error error;
  NodeFinder *nodeFinder = new TestNodeFinder();
  BOOST_CHECK(nodeFinder->start(&error));
  BOOST_CHECK(nodeFinder->stop(&error));
  delete nodeFinder;
}

BOOST_AUTO_TEST_CASE(RoundNodeFinderNotificationTest) {

  TestNodeFinder *nodeFinder = new TestNodeFinder();
  
  TestLocalNode testNode;
  
  BOOST_CHECK(nodeFinder->postNodeAdded(&testNode));
  BOOST_CHECK(nodeFinder->postNodeRemoved(&testNode));
  
  NotificationObserverList errorObservers;
  BOOST_CHECK(nodeFinder->postNodeAdded(&testNode, &errorObservers));
  BOOST_CHECK(nodeFinder->postNodeRemoved(&testNode, &errorObservers));
  
  delete nodeFinder;
}

BOOST_AUTO_TEST_SUITE_END()

