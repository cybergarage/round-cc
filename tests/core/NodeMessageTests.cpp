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

class TestNodeMessage : public NodeMessage {
public:
  TestNodeMessage() {}
  MessageType getType() {return 0;}
  
};

BOOST_AUTO_TEST_CASE(NodeMessageNewTest) {
  NodeMessage *msg = new TestNodeMessage();
  BOOST_CHECK(msg);
  delete msg;
}

