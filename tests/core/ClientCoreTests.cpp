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

#include <sstream>
#include <string.h>

#include <round/Round.h>

#include "RoundTest.h"
#include "TestClient.h"
#include "TestNode.h"
#include "TestFinder.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundClientCoreBaseTest) {
  const int nodeCount = 1;

  TestNodeFinder nodeFinder;
  Error error;

  // Setup Client
  TestClientCore client;
  nodeFinder.addObserver(&client);

  // Setup Nodes
  TestLocalNode **nodes = new TestLocalNode*[nodeCount];
  for (int n = 0; n < nodeCount; n++) {
    nodes[n] = new TestLocalNode(n);
    nodes[n]->setWeakFlag(true);
    nodeFinder.addObserver(nodes[n]);
    nodeFinder.postNodeAdded(nodes[n]);
  }

  // Clenup
  for (int n = 0; n < nodeCount; n++) {
    nodeFinder.postNodeRemoved(nodes[n]);
  }
  for (int n = 0; n < nodeCount; n++) {
    delete nodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundClientCoreTargetClusterTest) {
  TestClientCore client;

  const std::string clusterA = "testClusterA";
  const std::string clusterB = "testClusterB";
  const std::string clusterC = "testClusterC";
  
  // Initial Check
  
  Cluster *targetCluster;
  
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(!targetCluster);
  BOOST_CHECK(!client.setTargetCluster(clusterA));
  BOOST_CHECK(!client.setTargetCluster(clusterB));
  BOOST_CHECK(!client.setTargetCluster(clusterC));

  // Add New Clusters
  
  BOOST_CHECK(client.addCuster(clusterA));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterA.compare(targetCluster->getName()) == 0);
  
  BOOST_CHECK(client.addCuster(clusterB));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterA.compare(targetCluster->getName()) == 0);

  BOOST_CHECK(client.addCuster(clusterC));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterA.compare(targetCluster->getName()) == 0);

  // Set Traget Cluster
  
  BOOST_CHECK(client.setTargetCluster(clusterA));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterA.compare(targetCluster->getName()) == 0);

  BOOST_CHECK(client.setTargetCluster(clusterB));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterB.compare(targetCluster->getName()) == 0);

  BOOST_CHECK(client.setTargetCluster(clusterC));
  targetCluster = client.getTargetCluster();
  BOOST_CHECK(targetCluster);
  BOOST_CHECK(clusterC.compare(targetCluster->getName()) == 0);
}
