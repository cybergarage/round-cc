/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTLOCALNODE_H_
#define _ROUNDCC_TESTLOCALNODE_H_

#include <sstream>
#include <string>
#include <round/core/LocalNode.h>
#include <round/core/ServerNode.h>

#include "RoundTest.h"

class TestLocalNode : public Round::LocalNode {
 public:
  TestLocalNode() {
    initialize();
    this->port = 0;
  }

  TestLocalNode(int prefixNumber) {
    initialize();
    this->address = "";
    this->port = prefixNumber;
  }

  TestLocalNode(const char *addr, int port) {
    initialize();
    this->address = addr;
    this->port = port;
  }

  bool getName(std::string *buffer, Round::Error *error) const {
    std::stringstream prefix;
    prefix << this->port;
    *buffer = prefix.str();
    return true;
  }
  
  void setRequestPort(int value) {
    this->port = value;
  }

  void setRequestAddress(const char *value) {
    this->address = value;
  }

  bool getRequestAddress(std::string *address, Round::Error *error) const {
    *address = this->address;
    return true;
  }
  
  bool getRequestPort(int *port,  Round::Error *error) const {
    *port = this->port;
    return true;
  }
  
  bool getClusterName(std::string *name,  Round::Error *error) {
    return true;
  }

  Round::NodeGraph *getNodeGraph() {
    return Round::LocalNode::getNodeGraph();
  }
  
  void setWeakFlag(bool flag) {
    Node::setWeakFlag(flag);
  }

private:

  void initialize() {
    getNodeConfig()->setDatabaseDirectory(".");
  }
  
  std::string address;
  int port;
};

class TestServerNode : public Round::ServerNode {
 public:
  TestServerNode() {
  }

  bool start(Round::Error *error) {return true;}
  bool isRunning() {return true;}
  bool stop(Round::Error *error) {return true;}
};

class NodeTestController {
 public:
  
  NodeTestController() {
  }

  void runScriptManagerTest(Round::Node *node);
  void runSystemMethodTest(Round::Node *node);

 private:
  void runSystemGetNodeInfoTest(Round::Node *node);
  void runSystemGetClusterInfoTest(Round::Node *node);
  void runSystemGetNetworkInfoTest(Round::Node *node);
};

#endif
