/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_CLUSTER_H_
#define _ROUNDCC_CLUSTER_H_

#include <vector>
#include <string>

#include <round/core/NodeGraph.h>

namespace Round {

class Cluster {

 public:
  Cluster();
  Cluster(const Cluster *cluster);
  Cluster(const std::string &value);

  virtual ~Cluster();

  void setName(const std::string &value) {
    this->name = value;
  }

  const char *getName() const {
    return this->name.c_str();
  }

  bool isName(const std::string &value) const {
    return (this->name.compare(value) == 0) ? true : false;
  }

  bool equals(const Cluster *otherCluster) const ;

  bool equals(const Cluster otherCluster) const {
    return equals(&otherCluster);
  }
  
  // Node Graph
  
  const NodeGraph *getNodeGraph() const {
    return &nodeGraph;
  }
  
  bool addNode(Node *node) {
    return this->nodeGraph.addNode(node);
  }

  bool removeNode(Node *node) {
    return this->nodeGraph.removeNode(node);
  }
  
  bool hasNode(const Node *node) const {
    return this->nodeGraph.hasNode(node);
  }
  
  bool isLeaderNode(const Node *node) const {
    return this->nodeGraph.isLeaderNode(node);
  }
  
  Node *getNode(size_t index) const {
    return this->nodeGraph.getNode(index);
  }
  
  Node *getRandomNode() const {
    return this->nodeGraph.getRandomNode();
  }
  
  Node *getNodeByHashCode(const std::string &hashCode) const {
    return this->nodeGraph.getNodeByHashCode(hashCode);
  }
  
  size_t getNodeSize() const {
    return this->nodeGraph.size();
  }
  
private:

  std::string name;
  NodeGraph nodeGraph;
};

class ClusterList : public std::vector<Cluster *> {
  
 public:
  
  ClusterList();
  virtual ~ClusterList();

  bool addCluster(Cluster *cluster);

  Cluster *getCluster(size_t index) const {
    return at(index);
  }

  Cluster *getFirstCluster() const {
    if (size() <= 0)
      return NULL;
    return at(0);
  }
  
  Cluster *getCluster(const std::string &name) const;

  bool hasCluster(Cluster *cluster) const;
  bool hasCluster(const std::string &name) const;

  bool removeCluster(Cluster *cluster);
  bool removeCluster(const std::string &name);

  bool clear();
};

}

#endif
