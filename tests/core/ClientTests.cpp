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

#include "TestClient.h"
#include "TestServer.h"

using namespace std;
using namespace Round;

static const std::string FRACTAL_CLIENT_TEST_CLUSTER_NAME = "client_test_cluster";

BOOST_AUTO_TEST_CASE(RoundClientFinderTest) {
  Error error;
  
  TestServer server;
  LocalNodeConfig *serverConfig = server.getNodeConfig();
  BOOST_CHECK(serverConfig);
  BOOST_CHECK(serverConfig->setCluster(FRACTAL_CLIENT_TEST_CLUSTER_NAME));
  BOOST_CHECK(server.start(&error));

  BOOST_MESSAGE("Server (" << server.getRequestAddress() << ":" << server.getRequestPort() << ") is started");
  
  TestClient client;
  BOOST_CHECK(!client.setTargetCluster(FRACTAL_CLIENT_TEST_CLUSTER_NAME));
  BOOST_CHECK_EQUAL(client.getClusterCount(), 0);
  BOOST_CHECK(client.start(&error));
  
  while (client.getClusterCount() < 1) {
    BOOST_MESSAGE("Cluster " << FRACTAL_CLIENT_TEST_CLUSTER_NAME << " isn't found");
    
    BOOST_CHECK(server.announce());
    BOOST_MESSAGE("Server (" << server.getRequestAddress() << ":" << server.getRequestPort() << ") is announced");
    Round::Test::Sleep();
    
    BOOST_MESSAGE("Searing " << FRACTAL_CLIENT_TEST_CLUSTER_NAME << " ....");
    BOOST_CHECK(client.search(&error));
    Round::Test::Sleep();
  }

  BOOST_CHECK(server.stop(&error));
  BOOST_CHECK(client.stop(&error));
}