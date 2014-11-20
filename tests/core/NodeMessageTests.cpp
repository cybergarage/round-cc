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

#include <round/core/NodeMessage.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(NodeMessageNewTest) {
  NodeMessage *msg = new NodeMessage();
  BOOST_CHECK(msg);
  delete msg;
}

