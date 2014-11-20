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

class TestNodeResponse : public NodeResponse {
public:
  TestNodeResponse() {}
  MessageType getType() {return 0;}
};

BOOST_AUTO_TEST_CASE(NodeResponseNewTest) {
  NodeResponse *res = new TestNodeResponse();
  BOOST_CHECK(res);
  delete res;
}

