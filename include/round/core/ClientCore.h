/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CLIENTCORE_H_
#define _ROUNDCC_CLIENTCORE_H_

#include <round/common/Mutex.h>
#include <round/core/Cluster.h>
#include <round/core/NodeFinder.h>
#include <round/core/NodeMessage.h>

namespace Round {
  
class ClientCore : public NodeFinderObserver {
  
public:
  
  ClientCore();
  virtual ~ClientCore();
  
 public:

  Cluster *getTargetCluster() const ;

  const ClusterList *getClusters() const {
    return &clusterList;
  }
  
  Cluster *getClusterForNode(Node *node) const;
  
  Cluster *getCluster(const std::string &name) const;
  
  size_t getClusterCount() const {
    return clusterList.size();
  }
  
  bool hasTargetCluster(const std::string &clusterName) const;
  
  bool setTargetCluster(const std::string &clusterName);
  bool addCluster(const std::string &name);
  
  bool postMessage(NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

protected:

  void setTargetCluster(Cluster *cluster) {
    this->targetCluster = cluster;
  }
  
  bool addCluster(Node *node);
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

private:
  
  bool findObjectNode(const std::string &obj, Node **node, Error *error);

private:

  Mutex mutex;
  ClusterList clusterList;
  Cluster *targetCluster;
};

}

#endif
