/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_BASENODE_H_
#define _ROUNDCC_BASENODE_H_

#include <string>
#include <vector>

#include <round/core/NodeCore.h>

namespace Round {

class NodeGraph;

class Node : public NodeCore {
 public:
  static const std::string NAME;
  static const std::string VER;

 public:
  Node();
  virtual ~Node();

 public:
  
  bool getCluster(Cluster *cluster, Error *error = NULL) const;
  bool getName(std::string *buffer, Error *error = NULL) const;
  bool getVersion(std::string *buffer, Error *error = NULL) const;
  bool getStatus(NodeStatus *status, Error *error = NULL) const;
  bool getNodeGraph(NodeGraph *nodeGraph, Error *error = NULL);

 public:

  bool hasName() const;

public:
  
  bool isWeak() const {
    return this->weakFlag;
  }
  
protected:
  
  void setWeakFlag(bool flag) {
    this->weakFlag = flag;
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
};
  

}

#endif