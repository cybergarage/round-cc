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
#include <round/core/NodeCore.h>
#include <round/core/NodeStatus.h>
#include <round/core/Cluster.h>

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
  bool getStatus(NodeStatus *status, Error *error);
  bool getCluster(Cluster *cluster, Error *error);
  bool getClusterList(ClusterList *clusterList, Error *error);

public:

  void setWeakFlag(bool flag) {
    this->weakFlag = flag;
  }
  
  bool isWeak() const {
    return this->weakFlag;
  }
  
private:
  
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

  void clear();
};

}

#endif
