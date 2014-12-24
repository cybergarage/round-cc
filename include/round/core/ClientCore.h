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
  
protected:

  void setTargetCluster(Cluster *cluster) {
    this->targetCluster = cluster;
  }
  
  bool addCluster(Node *node);
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

private:

  Mutex mutex;
  ClusterList clusterList;
  Cluster *targetCluster;
};

}

#endif
