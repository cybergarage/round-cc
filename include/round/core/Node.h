/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODE_H_
#define _ROUNDCC_NODE_H_

#include <string>
#include <vector>

#include <round/common/Cloneable.h>
#include <round/common/Error.h>
#include <round/common/Mutex.h>
#include <round/core/NodeCore.h>
#include <round/core/NodeStatus.h>
#include <round/core/Cluster.h>
#include <round/core/Registry.h>

namespace Round {

class NodeGraph;

class Node : public NodeCore, public Cloneable<Node> {
 public:
  static const std::string NAME;
  static const std::string VER;

 public:
  Node();
  virtual ~Node();

 public:
  
  bool isAlive(Error *error);
  bool isLeader(Error *error);
  
  bool getStatus(NodeStatus *status, Error *error);
  bool getCluster(Cluster *cluster, Error *error);
  bool getClusterList(ClusterList *clusterList, Error *error);
  
  virtual bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) = 0;
  virtual bool postMessage(const NodeBatchRequest *nodeReq, NodeBatchResponse *nodeRes, Error *error) = 0;
  
  bool postMessage(const std::string &method, const std::string &params, std::string *result);
  bool findNode(const std::string &nodeHash, Node **node, Error *error);
  
  bool setRegistry(const Registry reg, Error *error);
  bool setRegistry(const std::string &key, const std::string &value, Error *error);
  bool getRegistry(const std::string &key, Registry *reg, Error *error);
  bool getRegistry(const std::string &key, std::string *value, Error *error);

public:

  void setWeakFlag(bool flag) {
    this->weakFlag = flag;
  }
  
  bool isWeak() const {
    return this->weakFlag;
  }
  
  void lock() {
    this->mutex.lock();
  }
  
  void unlock() {
    this->mutex.unlock();
  }
  
private:
  
  bool weakFlag;
  Mutex mutex;
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

  void clear();
};

}

#endif
