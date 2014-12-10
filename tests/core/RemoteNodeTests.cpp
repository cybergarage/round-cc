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

#include <round/core/RemoteNode.h>
#include <round/Server.h>

#include "TestNode.h"
#include "TestServer.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundRemoteNodeTest) {
for (int n = 0; n < 200; n+=10) {
    stringstream addr;
    addr << n << "." << n << "." << n << "." << n;
    RemoteNode testNode(addr.str(), n);
    RemoteNode remoteNode(&testNode);
    BOOST_CHECK_EQUAL(addr.str().compare(remoteNode.getRequestAddress()), 0);
    BOOST_CHECK_EQUAL(n, remoteNode.getRequestPort());
  }
}

BOOST_AUTO_TEST_CASE(RemoteNodeScriptManagerTest) {
  Error err;
  
  TestServer serverNode;
  BOOST_CHECK(serverNode.start(&err));

  std::string serverIp = serverNode.getRequestAddress();
  int serverPort = serverNode.getRequestPort();
  
  RemoteNode node(serverIp, serverPort);
  NodeTestController nodeTestController;
  nodeTestController.runScriptManagerTest(&node);

  BOOST_CHECK(serverNode.stop(&err));
}
