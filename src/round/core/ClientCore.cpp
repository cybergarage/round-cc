/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <round/core/ClientCore.h>
#include <round/core/Node.h>
#include <round/common/RPC.h>
#include <round/ui/console/Command.h>

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

bool Round::ClientCore::hasTargetCluster(const std::string &clusterName) const {
  Round::Cluster *targetCluster = getCluster(clusterName);
  if (!targetCluster)
    return false;
  return true;
}

Round::Cluster *Round::ClientCore::getTargetCluster() const {
  if (this->targetCluster)
    return targetCluster;
  return this->clusterList.getFirstCluster();
}

bool Round::ClientCore::addCluster(Round::Node *node) {
  std::string nodeClusterName;
  Error err;
  if  (!node->getClusterName(&nodeClusterName, &err))
    return false;
  return addCluster(nodeClusterName);
}

bool Round::ClientCore::addCluster(const std::string &name) {
  Cluster *cluster = new Cluster();
  if (!cluster)
    return false;
  cluster->setName(name);
  return this->clusterList.addCluster(cluster);
}

Round::Cluster *Round::ClientCore::getClusterForNode(Round::Node *node) const {
  std::string nodeClusterName;
  Error err;
  if (!node->getClusterName(&nodeClusterName, &err)) {
    return NULL;
  }
  return this->clusterList.getCluster(nodeClusterName);
}

Round::Cluster *Round::ClientCore::getCluster(const std::string &name) const {
  return this->clusterList.getCluster(name);
}

bool Round::ClientCore::findObjectNode(const std::string &obj, Node **foundNode, Error *err) {
  std::vector<std::string> objList;
  boost::split(objList, obj, boost::is_any_of(Round::Console::method::OBJECT_SEP));
  if (objList.size() <= 0 && 2 < objList.size()) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(Console::method::ERROR_OBJECT_NOTSPECEFIED);
    return false;
  }
  
  std::string cluster;
  std::string node;

  if (objList.size() == 2) {
    cluster = objList.at(0);
    node = objList.at(1);
  }
  else {
    node = objList.at(0);
  }

  // Select cluster
  
  Cluster *targetCluster = getTargetCluster();
  if (0 < cluster.length()) {
    targetCluster = getCluster(cluster);
  }

  if (!targetCluster) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(Console::method::ERROR_CLUSTER_NOTFOUND);
    return false;
  }

  // Select node
  
  if (node.length() <= 0) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(Console::method::ERROR_NODE_NOTFOUND);
    return false;
  }
  
  Node *targetNode = NULL;
  if (node.compare(NodeRequest::ANY) == 0) {
    targetNode = targetCluster->getRandomNode();
  }
  else {
    try {
      size_t nodeIdx = boost::lexical_cast<size_t>(node);
      targetNode = targetCluster->getNode(nodeIdx);
    } catch(boost::bad_lexical_cast &) {
      targetNode = targetCluster->getNodeByHashCode(node);
    }
  }

  if (!targetNode) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(Console::method::ERROR_NODE_NOTFOUND);
    return false;
  }
  
  return false;
}

bool Round::ClientCore::postMessage(NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  std::string dest;
  if (!nodeReq->getDest(&dest)) {
    dest = NodeRequest::ANY;
  }
  
  Node *destNode;
  if (!findObjectNode(dest, &destNode, err)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMovedPermanently, err);
    return false;
  }

  if (!nodeReq->isDestAll()) {
    nodeReq->setDest(destNode);
  }
  
  return destNode->postMessage(nodeReq, nodeRes, err);
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
    if (targetCluster->addNode(node)) {
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
    if (targetCluster->removeNode(node)) {
      isNodeRemoved = true;
    }
  }

  this->mutex.unlock();

  return isNodeRemoved;
}
