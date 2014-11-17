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

#include <round/core/NodeRequest.h>

using namespace std;
using namespace Round;

class TestNodeRequest : public NodeRequest {
public:
  TestNodeRequest() {}
  MessageType getType() {return 0;}
  
};

BOOST_AUTO_TEST_CASE(NodeRequestNewTest) {
  NodeRequest *req = new TestNodeRequest();
  BOOST_CHECK(req);
  delete req;
}

