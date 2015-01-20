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
#include <string.h>

#include <round/Round.h>

#include "RoundTest.h"
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(LocalNodeEqualTest) {
  TestLocalNode localNode01("192.168.0.1", 80);
  TestLocalNode localNode02("192.168.0.1", 80);
  TestLocalNode localNode03("192.168.0.2", 80);
  TestLocalNode localNode04("192.168.0.1", 81);
  TestLocalNode localNode05("192.168.0.2", 81);
  
  BOOST_CHECK(localNode01.equals(&localNode01));
  BOOST_CHECK(localNode01.equals(&localNode02));
  BOOST_CHECK(!localNode01.equals(&localNode03));
  BOOST_CHECK(!localNode01.equals(&localNode04));
  BOOST_CHECK(!localNode01.equals(&localNode05));
}

BOOST_AUTO_TEST_CASE(LocalNodConfigGraphTest) {
  LocalConfig nodeConfig;
  Error error;
  std::string retStringValue;
  int retIntValue;
  
  const std::string testHttpAddr = "testAddr";
  BOOST_CHECK(nodeConfig.setHttpdBindAddress(testHttpAddr));
  BOOST_CHECK_EQUAL(nodeConfig.getHttpdBindAddress(&retStringValue, &error), true);
  BOOST_CHECK_EQUAL(testHttpAddr, retStringValue);
  
  const int testHttpdPort = 8483;
  BOOST_CHECK_EQUAL(nodeConfig.getHttpdBindPort(&retIntValue, &error), false);
  BOOST_CHECK(nodeConfig.setHttpdBindPort(testHttpdPort));
  BOOST_CHECK_EQUAL(nodeConfig.getHttpdBindPort(&retIntValue, &error), true);
  BOOST_CHECK_EQUAL(testHttpdPort, retIntValue);
  
  const std::string testCluster = "testCluster";
  BOOST_CHECK_EQUAL(nodeConfig.getCluster(&retStringValue, &error), false);
  BOOST_CHECK(nodeConfig.setCluster(testCluster));
  BOOST_CHECK_EQUAL(nodeConfig.getCluster(&retStringValue, &error), true);
  BOOST_CHECK_EQUAL(testCluster, retStringValue);
  
  const std::string testDatabaseDir = "testDir";
  BOOST_CHECK_EQUAL(nodeConfig.getDatabaseDirectory(&retStringValue, &error), false);
  BOOST_CHECK(nodeConfig.setDatabaseDirectory(testDatabaseDir));
  BOOST_CHECK_EQUAL(nodeConfig.getDatabaseDirectory(&retStringValue, &error), true);
  BOOST_CHECK_EQUAL(testDatabaseDir, retStringValue);
  
  const std::string testLogFilename = "testLogFilename";
  BOOST_CHECK_EQUAL(nodeConfig.getLogFilename(&retStringValue, &error), false);
  BOOST_CHECK(nodeConfig.setLogFilename(testLogFilename));
  BOOST_CHECK_EQUAL(nodeConfig.getLogFilename(&retStringValue, &error), true);
  BOOST_CHECK_EQUAL(testLogFilename, retStringValue);
  
  const std::string testErrorLogFilename = "testErrorFilename";
  BOOST_CHECK_EQUAL(nodeConfig.getErrorLogFilename(&retStringValue, &error), false);
  BOOST_CHECK(nodeConfig.setErrorLogFilename(testErrorLogFilename));
  BOOST_CHECK_EQUAL(nodeConfig.getErrorLogFilename(&retStringValue, &error), true);
  BOOST_CHECK_EQUAL(testErrorLogFilename, retStringValue);
}

BOOST_AUTO_TEST_CASE(LocalNodMemoryTest) {
  TestLocalNode node;
  
  string key = "key";
  string value;
  string valueBuf;
  
  BOOST_CHECK_EQUAL(node.getKey(key, &valueBuf), false);
  
  value = "hello";
  BOOST_CHECK(node.setKey(key, value));
  BOOST_CHECK_EQUAL(node.getKey(key, &valueBuf), true);
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);
  
  value = "world";
  BOOST_CHECK(node.setKey(key, value));
  BOOST_CHECK_EQUAL(node.getKey(key, &valueBuf), true);
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(LocalScriptManagerTest) {
  TestLocalNode node;
  NodeTestController nodeTestController;
  nodeTestController.runScriptManagerTest(&node);
}

BOOST_AUTO_TEST_CASE(LocalNodeSystemMethodTest) {
  Error err;
  TestLocalNode node;
  
  BOOST_CHECK(node.start(&err));
  
  NodeTestController nodeTestController;
  nodeTestController.runSystemMethodTest(&node);

  BOOST_CHECK(node.stop(&err));
}

namespace Round {

static TestLocalNode **LocalNodeTestCreateNodes(size_t nodeCnt) {
  Error err;
  
  // Setup Nodes
  TestLocalNode **nodes = new TestLocalNode*[nodeCnt];
  for (int n = 0; n < nodeCnt; n++) {
    nodes[n] = new TestLocalNode(n);
    nodes[n]->setWeakFlag(true);
    BOOST_CHECK(nodes[n]->start(&err));
  }
  
  // Setup NodeGraph
  for (int i = 0; i < nodeCnt; i++) {
    for (int j = 0; j < nodeCnt; j++) {
      BOOST_CHECK(nodes[i]->nodeAdded(nodes[j]));
    }
    NodeGraph *nodeGraph = nodes[i]->getNodeGraph();
    BOOST_CHECK_EQUAL(nodeGraph->size(), nodeCnt);
  }
  
  return nodes;
}

static void LocalNodeTestDeleteNodes(TestLocalNode **nodes, size_t nodeCnt) {
  Error err;

  // Clenup
  for (int n = 0; n < nodeCnt; n++) {
    BOOST_CHECK(nodes[n]->stop(&err));
    delete nodes[n];
  }
  delete []nodes;
}

}

BOOST_AUTO_TEST_CASE(LocalNodeHashRequestTest) {
  const size_t TEST_NODE_COUNT = 10;
  
  // Setup Nodes
  TestLocalNode **nodes = Round::LocalNodeTestCreateNodes(TEST_NODE_COUNT);
  
  // Test Hash Parameter
  NodeTestController nodeTestController;
  nodeTestController.runRpcTest((Node **)nodes, TEST_NODE_COUNT);
  
  // Clenup
  Round::LocalNodeTestDeleteNodes(nodes, TEST_NODE_COUNT);
}

BOOST_AUTO_TEST_CASE(LocalNodeGetAllOtherNodesTest) {
  const size_t TEST_NODE_COUNT = 10;
  
  // Setup Nodes
  TestLocalNode **nodes = Round::LocalNodeTestCreateNodes(TEST_NODE_COUNT);
  
  // Setup NodeGraph
  for (size_t n = 0; n<TEST_NODE_COUNT; n++) {
    NodeList nodeList;
    BOOST_CHECK(nodes[n]->getAllOtherNodes(&nodeList));
    BOOST_CHECK_EQUAL(nodeList.size(), (TEST_NODE_COUNT-1));
  }
  
  // Clenup
  Round::LocalNodeTestDeleteNodes(nodes, TEST_NODE_COUNT);
}

BOOST_AUTO_TEST_CASE(LocalNodeGetQuorumNodesTest) {
  const size_t TEST_NODE_COUNT = 10;
  
  // Setup Nodes
  TestLocalNode **nodes = Round::LocalNodeTestCreateNodes(TEST_NODE_COUNT);
  
  // Setup NodeGraph
  for (size_t n = 0; n< TEST_NODE_COUNT; n++) {
    for (size_t i = 0; i<TEST_NODE_COUNT; i++) {
      NodeList nodeList;
      BOOST_CHECK(nodes[n]->getQuorumNodes(&nodeList, i));
      BOOST_CHECK_EQUAL(nodeList.size(), i);
    }
  }
  
  // Clenup
  Round::LocalNodeTestDeleteNodes(nodes, TEST_NODE_COUNT);
}

BOOST_AUTO_TEST_SUITE_END()
