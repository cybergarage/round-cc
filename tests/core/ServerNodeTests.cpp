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

#include <round/Round.h>
#include "TestNode.h"

using namespace Round;

BOOST_AUTO_TEST_SUITE(server)

BOOST_AUTO_TEST_CASE(RoundServerNodeTest) {
  Error err;

  TestServerNode *nodeServer = new TestServerNode();
  nodeServer->start(&err);
  nodeServer->stop(&err);
  delete nodeServer;
}

BOOST_AUTO_TEST_SUITE_END()
