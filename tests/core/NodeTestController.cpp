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
#include <round/core/SystemMethod.h>

#include "TestNode.h"
#include "TestScript.h"

using namespace std;
using namespace Round;

void NodeTestController::runScriptManagerTest(Node *node) {

  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;
  clock_t prevClock, postClock;
  
  // Post Node Message (Overide '_set_method' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_SETMETHOD));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method without method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK_EQUAL(error.getDetailCode(), RPC::JSON::ErrorCodeMethodNotFound);
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Set 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Override 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);

  // Post Node Message (Remove 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  prevClock = node->getLocalClock();
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);

  prevClock = node->getLocalClock();
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK_EQUAL(error.getDetailCode(), RPC::JSON::ErrorCodeMethodNotFound);
  postClock = node->getLocalClock();
  BOOST_CHECK(prevClock < postClock);
}

void NodeTestController::runSystemGetNodeInfoTest(Round::Node *node) {
  Error err;
  std::string jsonString;
  
  // Node information
  
  std::string nodeIp;
  BOOST_CHECK(node->getRequestAddress(&nodeIp, &err));
  
  int nodePort;
  BOOST_CHECK(node->getRequestPort(&nodePort, &err));
  
  std::string nodeCluster;
  BOOST_CHECK(node->getClusterName(&nodeCluster, &err));

  std::string nodeHash;
  BOOST_CHECK(node->getHashCode(&nodeHash));
  
  // Response information

  SystemGetNodeInfoRequest nodeReq;
  NodeResponse nodeRes;
  
  nodeReq.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  BOOST_CHECK(node->postMessage(&nodeReq, &nodeRes, &err));

  nodeRes.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());

  SystemGetNodeInfoResponse sysRes(&nodeRes);
  
  std::string resIp;
  BOOST_CHECK(sysRes.getIp(&resIp));
  
  int resPort;
  BOOST_CHECK(sysRes.getPort(&resPort));
  
  std::string resCluster;
  BOOST_CHECK(sysRes.getCluster(&resCluster));
  
  std::string resHash;
  BOOST_CHECK(sysRes.getHash(&resHash));

  // Compare information

  BOOST_CHECK_EQUAL(nodeIp.compare(resIp), 0);
  BOOST_CHECK_EQUAL(nodePort, resPort);
  BOOST_CHECK_EQUAL(nodeCluster.compare(resCluster), 0);
  BOOST_CHECK_EQUAL(nodeHash.compare(resHash), 0);
}

void NodeTestController::runSystemGetClusterInfoTest(Round::Node *node) {
  Error err;
  std::string jsonString;
  
  // Node information
  
  std::string nodeIp;
  BOOST_CHECK(node->getRequestAddress(&nodeIp, &err));
  
  int nodePort;
  BOOST_CHECK(node->getRequestPort(&nodePort, &err));
  
  std::string nodeCluster;
  BOOST_CHECK(node->getClusterName(&nodeCluster, &err));
  
  std::string nodeHash;
  BOOST_CHECK(node->getHashCode(&nodeHash));
  
  // Response information
  
  SystemGetClusterInfoRequest nodeReq;
  NodeResponse nodeRes;
  
  nodeReq.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  BOOST_CHECK(node->postMessage(&nodeReq, &nodeRes, &err));
  
  nodeRes.toJSONString(&jsonString);
  RoundLogTrace(jsonString.c_str());
  
  SystemGetClusterInfoResponse sysRes(&nodeRes);
  
  Cluster cluster;
  BOOST_CHECK(sysRes.getCluster(&cluster));

  BOOST_CHECK(cluster.hasNode(node));
}

void NodeTestController::runSystemMethodTest(Round::Node *node) {
  // _get_node_info
  runSystemGetNodeInfoTest(node);
  
  // _get_cluster_info
  runSystemGetClusterInfoTest(node);
}
