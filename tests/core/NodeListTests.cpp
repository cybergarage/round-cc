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

#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundNodeListBasicTest) {
const int testNodeCount = 10;

  for (int n = 0; n < testNodeCount; n++) {
  
    TestLocalNode *nodes[n];
    NodeList srcNodeList;
    NodeList destNodeList;
  
    for (int i = 0; i<n; i++) {
      nodes[i] = new TestLocalNode();
      srcNodeList.addNode(nodes[i]);
    }
  
    destNodeList.set(&srcNodeList);
    BOOST_CHECK_EQUAL(srcNodeList.size(), destNodeList.size());
  
    for (int i = 0; i<n; i++) {
      BOOST_CHECK_EQUAL(srcNodeList.getNode(i), destNodeList.getNode(i));
    }
    for (int i = 0; i<n; i++)
      delete nodes[i];
  
  }
}
