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

#include "TestNode.h"
#include "TestScript.h"

using namespace std;
using namespace Round;

void NodeTestController::runScriptManagerTest(Node *node) {

  NodeRequestParser reqParser;
  
  NodeRequest *nodeReq;
  NodeResponse nodeRes;
  Error error;

  // Post Node Message (Overide '_set_method' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_SETMETHOD));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  
  // Post Node Message (Run 'echo' method without method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK_EQUAL(error.getDetailCode(), RPC::JSON::ErrorCodeMethodNotFound);
  
  // Post Node Message (Set 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Post Node Message (Override 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_SET_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));

  // Post Node Message (Remove 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_REMOVE_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(node->postMessage(nodeReq, &nodeRes, &error));
  
  // Post Node Message (Run 'echo' method)
  
  BOOST_CHECK(reqParser.parse(Test::RPC_RUN_ECHO));
  BOOST_CHECK(reqParser.getObject()->isDictionary());
  nodeReq = dynamic_cast<NodeRequest *>(reqParser.getObject());
  BOOST_CHECK(nodeReq);
  
  BOOST_CHECK(!node->postMessage(nodeReq, &nodeRes, &error));
  BOOST_CHECK_EQUAL(error.getDetailCode(), RPC::JSON::ErrorCodeMethodNotFound);
}
