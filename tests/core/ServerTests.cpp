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

#include <round/Client.h>

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

BOOST_AUTO_TEST_CASE(RoundRealServerClientFindTest) {
  Error err;
  
  static const int TEST_SERVER_COUNT = 2;
  
  // Start Server
  
  TestServer **servers = new TestServer*[TEST_SERVER_COUNT];
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    servers[n] = new TestServer();
    BOOST_CHECK(servers[n]->start(&err));
    Round::Test::Sleep();
  }
  
  // Client
  
  Client client;
  BOOST_CHECK(client.start(&err));
  BOOST_CHECK(client.stop(&err));
  
  // Stop Server
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    BOOST_CHECK(servers[n]->stop(&err));
    delete servers[n];
  }
  
  delete[] servers;
}

BOOST_AUTO_TEST_CASE(RoundRealServerEachFindTest) {
  Error err;

  static const int TEST_SERVER_COUNT = 2;
  
  // Start Server
  
  TestServer **servers = new TestServer*[TEST_SERVER_COUNT];
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    servers[n] = new TestServer();
    BOOST_CHECK(servers[n]->start(&err));
    Round::Test::Sleep();
  }
  
  // Find each servers

  bool isServerNotFound = true;
  while (isServerNotFound) {
    isServerNotFound = false;
    for (int n=0; n<TEST_SERVER_COUNT; n++) {
      Cluster cluster;
      BOOST_CHECK(servers[n]->getCluster(&cluster, &err));
      BOOST_WARN_MESSAGE((cluster.size() != TEST_SERVER_COUNT), "Server not found (" << cluster.size() << ") !!");
      if (cluster.size() != TEST_SERVER_COUNT) {
        isServerNotFound = true;
        break;
      }
    }
    if (isServerNotFound) {
      for (int n=0; n<TEST_SERVER_COUNT; n++) {
        BOOST_CHECK(servers[n]->announce());
        Round::Test::Sleep();
      }
    }
    Round::Test::Sleep();
  }

  // Client
  
  Client client;
  BOOST_CHECK(client.start(&err));
  BOOST_CHECK(client.stop(&err));
  
  // Stop Server
  
  for (int n=0; n<TEST_SERVER_COUNT; n++) {
    BOOST_CHECK(servers[n]->stop(&err));
    delete servers[n];
  }
  
  delete[] servers;
}

BOOST_AUTO_TEST_SUITE_END()
