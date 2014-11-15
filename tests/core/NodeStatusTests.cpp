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

#include <round/core/NodeStatus.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundNodStatusDefaultTest) {
  NodeStatus nodeStatus;
  BOOST_CHECK_EQUAL(nodeStatus.getState(), NodeStatus::UNKNOWN);
}

BOOST_AUTO_TEST_CASE(RoundNodStatusStringTest) {
  NodeStatus nodeStatus;
  string unknownStatus = NodeStatus::GetStateString(NodeStatus::UNKNOWN);
  for (int n = (NodeStatus::UNKNOWN + 1); n < NodeStatus::STATE_MAX; n++) {
    string nodeStatus = NodeStatus::GetStateString(n);
    BOOST_CHECK(unknownStatus.compare(nodeStatus) != 0);
  }
}

BOOST_AUTO_TEST_CASE(RoundNodStatusSetterTest) {
  NodeStatus nodeStatus;
  string nodeStatusString;
  nodeStatus.setState(NodeStatus::ACTIVE);
  nodeStatusString = nodeStatus.getStateString();
  BOOST_CHECK_EQUAL(nodeStatusString.compare(NodeStatus::GetStateString(NodeStatus::ACTIVE)), 0);
}

BOOST_AUTO_TEST_CASE(RoundNodStatusStringSetterTest) {
  NodeStatus nodeStatus;
  nodeStatus.setState(NodeStatus::GetStateString(NodeStatus::ACTIVE));
  BOOST_CHECK_EQUAL(nodeStatus.getState(), NodeStatus::ACTIVE);
}
