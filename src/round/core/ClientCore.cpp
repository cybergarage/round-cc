/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/core/ClientCore.h>
#include <round/core/Node.h>

Round::ClientCore::ClientCore() {
  setTargetCluster(NULL);
}

Round::ClientCore::~ClientCore() {
}

bool Round::ClientCore::setTargetCluster(const std::string &clusterName) {
  Round::Cluster *targetCluster = getCluster(clusterName);
  if (!targetCluster)
    return false;
  setTargetCluster(targetCluster);
  return true;
}

bool Round::ClientCore::hasTargetCluster(const std::string &clusterName) {
  Round::Cluster *targetCluster = getCluster(clusterName);
  if (!targetCluster)
    return false;
  return true;
}

Round::Cluster *Round::ClientCore::getTargetCluster() {
  if (this->targetCluster)
    return targetCluster;
  return this->clusterList.getFirstCluster();
}

bool Round::ClientCore::addCluster(Round::Node *node) {
  Cluster nodeCluster;
  if  (!node->getCluster(&nodeCluster))
    return false;
  return addCluster(nodeCluster.getName());
}

bool Round::ClientCore::addCluster(const std::string &name) {
  Cluster *cluster = new Cluster();
  if (!cluster)
    return false;
  cluster->setName(name);
  return this->clusterList.addCluster(cluster);
}

Round::Cluster *Round::ClientCore::getClusterForNode(Round::Node *node) {
  Cluster cluster;
  if (!node->getCluster(&cluster)) {
    return NULL;
  }
  return this->clusterList.getCluster(cluster.getName());
}

Round::Cluster *Round::ClientCore::getCluster(const std::string &name) {
  return this->clusterList.getCluster(name);
}

bool Round::ClientCore::nodeAdded(Round::Node *node)  {

  bool isNodeAdded = false;
  
  this->mutex.lock();

  Cluster *targetCluster = getClusterForNode(node);
  if (!targetCluster) {
    if (this->addCluster(node)) {
      targetCluster = getClusterForNode(node);
    }
  }

  if (targetCluster) {
    if (targetCluster->getNodeGraph()->addNode(node)) {
      isNodeAdded = true;
    }
  }

  this->mutex.unlock();

  return isNodeAdded;
}

bool Round::ClientCore::nodeRemoved(Round::Node *node)  {
  bool isNodeRemoved = false;
  
  this->mutex.lock();

  Cluster *targetCluster = getClusterForNode(node);
  if (targetCluster) {
    if (targetCluster->getNodeGraph()->removeNode(node)) {
      isNodeRemoved = true;
    }
  }

  this->mutex.unlock();

  return isNodeRemoved;
}
