/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODE_H_
#define _ROUNDCC_NODE_H_

#include <string>
#include <vector>

#include <round/common/ConsistentHash.h>
#include <round/common/Cloneable.h>
#include <round/common/Message.h>
#include <round/common/Dictionary.h>
#include <round/core/Cluster.h>
#include <round/core/ErrorNo.h>
#include <round/core/NodeStatus.h>

namespace Round {
class NodeGraph;

class Node : public ConsistentHashNode, public Cloneable<Node> {
 public:
  static const std::string NAME;
  static const std::string VER;

 public:
  Node();
  virtual ~Node();

 public:
  virtual bool getCluster(Cluster *cluster, Error *error = NULL) const = 0;
  virtual bool getName(std::string *buffer, Error *error = NULL) const = 0;
  virtual bool getVersion(std::string *buffer, Error *error = NULL) const = 0;
  virtual bool getStatus(NodeStatus *status, Error *error = NULL) const = 0;

  virtual int getRequestPort() const = 0;
  virtual const char *getRequestAddress() const = 0;
  
  virtual bool getNodeGraph(NodeGraph *nodeGraph, Error *error = NULL) = 0;

  virtual bool postMessage(const Message *msg) = 0;

 public:

  const char *getHashSeed(std::string *seedString) const;

 public:

  bool hasName() const;
  
  bool isWeak() const {
    return this->weakFlag;
  }

protected:

  void setWeakFlag(bool flag) {
    this->weakFlag = flag;
  }

private:

  std::string name;
  bool weakFlag;
};

class NodeList : public std::vector<Node *> {
  
public:
  
  NodeList();
  virtual ~NodeList();

  void set(const NodeList *nodeList);

  void addNode(Node *node) {
    push_back(node);
  }

  Node *getNode(size_t index) const {
    return at(index);
  }
};

}

#endif
