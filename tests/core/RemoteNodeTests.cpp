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

#include <round/core/RemoteNode.h>
#include <round/Server.h>

#include "TestNode.h"
#include "TestServer.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(RoundRemoteNodeConstructorTest) {
  for (int n = 0; n < 200; n+=10) {
    stringstream addr;
    addr << n << "." << n << "." << n << "." << n;
    RemoteNode remoteNode(addr.str(), n);
    
    Error error;
    std::string remoteAddr;
    
    BOOST_CHECK(remoteNode.getRequestAddress(&remoteAddr, &error));
    BOOST_CHECK_EQUAL(addr.str().compare(remoteAddr), 0);
    
    int remotePort;
    BOOST_CHECK(remoteNode.getRequestPort(&remotePort, &error));
    BOOST_CHECK_EQUAL(n, remotePort);

    BOOST_CHECK_EQUAL(remoteNode.hasClusterName(), false);
  }
}
    
BOOST_AUTO_TEST_CASE(RoundRemoteNodeCopyConstructorTest) {
  for (int n = 0; n < 200; n+=10) {
    stringstream addr;
    addr << n << "." << n << "." << n << "." << n;
    RemoteNode testNode(addr.str(), n);
    RemoteNode remoteNode(&testNode);
  
    Error error;
    std::string remoteAddr;
  
    BOOST_CHECK(remoteNode.getRequestAddress(&remoteAddr, &error));
    BOOST_CHECK_EQUAL(addr.str().compare(remoteAddr), 0);
  
    int remotePort;
    BOOST_CHECK(remoteNode.getRequestPort(&remotePort, &error));
    BOOST_CHECK_EQUAL(n, remotePort);

    BOOST_CHECK_EQUAL(remoteNode.hasClusterName(), false);
  }
}

BOOST_AUTO_TEST_CASE(RoundRemoteNodeSetterTest) {
  
  for (int n = 0; n < 200; n+=10) {
    RemoteNode remoteNode;
    
    stringstream addr;
    addr << n << "." << n << "." << n << "." << n;
    BOOST_CHECK(remoteNode.setRequestAddress(addr.str()));

    int port = n;
    BOOST_CHECK(remoteNode.setRequestPort(port));

    stringstream cluster;
    cluster << "cluster" << n;
    BOOST_CHECK(remoteNode.setClusterName(cluster.str()));
  
    Error error;

    std::string remoteAddr;
    BOOST_CHECK(remoteNode.getRequestAddress(&remoteAddr, &error));
    BOOST_CHECK_EQUAL(addr.str().compare(remoteAddr), 0);
      
    int remotePort;
    BOOST_CHECK(remoteNode.getRequestPort(&remotePort, &error));
    BOOST_CHECK_EQUAL(port, remotePort);

    std::string remoteCluster;
    BOOST_CHECK(remoteNode.getClusterName(&remoteCluster, &error));
    BOOST_CHECK_EQUAL(cluster.str().compare(remoteCluster), 0);
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(RemoteNodeScriptManagerTest) {
  Error err;
  
  TestServer serverNode;
  BOOST_CHECK(serverNode.start(&err));

  std::string serverIp;
  BOOST_CHECK(serverNode.getRequestAddress(&serverIp, &err));

  int serverPort;
  BOOST_CHECK(serverNode.getRequestPort(&serverPort, &err));
  
  RemoteNode node(serverIp, serverPort);
  NodeTestController nodeTestController;
  nodeTestController.runScriptManagerTest(&node);

  BOOST_CHECK(serverNode.stop(&err));
}
  
BOOST_AUTO_TEST_CASE(RemoteNodeSystemMethodTest) {
  Error err;
  
  TestServer serverNode;
  BOOST_CHECK(serverNode.start(&err));
  
  std::string serverIp;
  BOOST_CHECK(serverNode.getRequestAddress(&serverIp, &err));
  
  int serverPort;
  BOOST_CHECK(serverNode.getRequestPort(&serverPort, &err));
  
  RemoteNode node(serverIp, serverPort);
  NodeTestController nodeTestController;
  nodeTestController.runSystemMethodTest(&node);
  
  BOOST_CHECK(serverNode.stop(&err));
}

BOOST_AUTO_TEST_SUITE_END()
