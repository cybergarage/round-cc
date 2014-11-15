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

#include <round/core/LocalNodeConfig.h>

using namespace std;
using namespace Round;

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
