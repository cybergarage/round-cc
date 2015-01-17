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

#include <sstream>

#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

class BasicTestNode : public LocalNode {
 public:
  BasicTestNode() {
  }
};

BOOST_AUTO_TEST_CASE(RoundNodeBasicTest) {
  for (int n = 0; n < 10; n++) {
    TestLocalNode node;
  }
}

BOOST_AUTO_TEST_SUITE_END()
