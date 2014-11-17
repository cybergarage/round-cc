/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CLIENTCORE_H_
#define _ROUNDCC_CLIENTCORE_H_

#include <round/common/Mutex.h>
#include <round/common/Error.h>
#include <round/core/NodeFinder.h>
#include <round/core/Cluster.h>

namespace Round {
  
class ClientCore : public NodeFinderObserver {
  
public:
  
  ClientCore();
  virtual ~ClientCore();
  
 public:

  Cluster *getTargetCluster();

  ClusterList *getClusters() {
    return &clusterList;
  }
  
  size_t getClusterCount() {
    return clusterList.size();
  }
  
  bool setTargetCluster(const std::string &clusterName);
  bool hasTargetCluster(const std::string &clusterName);
  bool addCluster(const std::string &name);
  
protected:

  void setTargetCluster(Cluster *cluster) {
    this->targetCluster = cluster;
  }
  
  bool addCluster(Node *node);
  
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

  Cluster *getClusterForNode(Node *node);
  Cluster *getCluster(const std::string &name);

private:

  Mutex mutex;
  ClusterList clusterList;
  Cluster *targetCluster;
};

}

#endif
