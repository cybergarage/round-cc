/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <sstream>

#include "TestNode.h"

using namespace std;
using namespace Round;

class BasicTestNode : public LocalNode {
 public:
  BasicTestNode() {
  }

  int getRequestPort() {
    return 0;
  }

  const char *getRequestAddress() {
    return "";
  }
};

BOOST_AUTO_TEST_CASE(RoundNodeBasicTest) {
  for (int n = 0; n < 10; n++) {
    TestLocalNode node;
    BOOST_CHECK_EQUAL(node.hasName(), true);
  }
}

