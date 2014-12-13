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

BOOST_AUTO_TEST_CASE(LocalNodeBasisMethodTest) {
  TestLocalNode node;
  Error err;

  std::string version;
  BOOST_CHECK(node.getVersion(&version, &err));
  BOOST_CHECK(0 < version.length());

  Cluster cluster;
  std::string clusterName;
  BOOST_CHECK(node.getCluster(&cluster, &err));
  clusterName = cluster.getName();
  BOOST_CHECK(0 < clusterName.length());
}


BOOST_AUTO_TEST_CASE(LocalNodConfigGraphTest) {
  LocalNodeConfig nodeConfig;
  Error error;
  std::string retStringValue;
  int retIntValue;
  
  const std::string testHttpAddr = "testAddr";
  // LocalNodeConfig::getHttpdBindAddress() returns a default value when the value is not specified.
  //BOOST_CHECK_EQUAL(nodeConfig.getHttpdBindAddress(&retStringValue, &error), false);
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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(LocalNodeScriptManagerTest) {
  TestLocalNode node;
  NodeTestController nodeTestController;
  nodeTestController.runScriptManagerTest(&node);
}

BOOST_AUTO_TEST_SUITE_END()
