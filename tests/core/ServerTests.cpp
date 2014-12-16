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

#include "RoundTest.h"
#include "TestServer.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(server)

BOOST_AUTO_TEST_CASE(RoundRealServerRunTest) {
  Error err;

  Server *nodeServer = new TestServer();

  BOOST_CHECK(nodeServer->start(&err));

  BOOST_MESSAGE("Server is started");
  
  string httpHost;
  BOOST_CHECK(nodeServer->getRequestAddress(&httpHost, &err));
  BOOST_CHECK(0 < httpHost.length());

  int httpPort;
  BOOST_CHECK(nodeServer->getRequestPort(&httpPort, &err));
  BOOST_CHECK(0 < httpPort);
  
  BOOST_MESSAGE("Server : " << httpHost << ":" << httpPort);
  

  RemoteNode remoteNode(httpHost, httpPort);

  BOOST_MESSAGE("Server is stopped");
  
  delete nodeServer;
}

BOOST_AUTO_TEST_CASE(RoundRealServerFindTest) {
  Error err;

  static const int TEST_SERVER_COUNT = 2;
  
  TestServer **servers = new TestServer*[TEST_SERVER_COUNT];
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    servers[n] = new TestServer();
    BOOST_CHECK(servers[n]->start(&err));
    Round::Test::Sleep();
  }
  
  Round::Test::Sleep(1000 * 5);

  bool isServerNotFound = true;
  while (isServerNotFound) {
    isServerNotFound = false;
    for (int n=0; n<TEST_SERVER_COUNT; n++) {
      Cluster cluster;
      BOOST_CHECK(servers[n]->getCluster(&cluster, &err));
      NodeGraph *nodeGraph = cluster.getNodeGraph();
      BOOST_CHECK(nodeGraph);
      BOOST_CHECK_EQUAL(nodeGraph->size(), TEST_SERVER_COUNT);
      if (nodeGraph->size() != TEST_SERVER_COUNT) {
        isServerNotFound = true;
        break;
      }
    }
    Round::Test::Sleep();
  }
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    BOOST_CHECK(servers[n]->stop(&err));
    delete servers[n];
  }
  
  delete[] servers;
}

BOOST_AUTO_TEST_SUITE_END()

