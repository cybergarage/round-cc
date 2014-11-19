/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <round/Round.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>

Round::LocalNode::LocalNode() {
  init();
}

Round::LocalNode::~LocalNode() {
}

void Round::LocalNode::init() {
  setState(NodeStatus::STOP);
}

bool Round::LocalNode::nodeAdded(Round::Node *addedNode)  {
  Error error;
  
  Cluster addedNodeCluster;
  if (!addedNode->getCluster(&addedNodeCluster, &error))
    return false;
  
  Cluster thisNodeCluster;
  if (!getCluster(&thisNodeCluster, &error))
    return false;
  
  if (!thisNodeCluster.equals(addedNodeCluster))
    return false;
  
  if (this->nodeGraph.hasNode(addedNode))
    return true;

  if (!this->nodeGraph.addNode(addedNode))
    return true;
  
  if (equals(addedNode))
    return true;
  
  setState(NodeStatus::OPTIMIZING);
  
  return true;
}

bool Round::LocalNode::nodeRemoved(Round::Node *removedNode)  {
  if (!this->nodeGraph.hasNode(removedNode))
    return true;
  
  if (equals(removedNode)) {
    this->nodeGraph.removeNode(removedNode);
    return true;
  }
      
  ssize_t removedNodeIndex = this->nodeGraph.getNodeIndex(removedNode);
  if (removedNodeIndex < 0)
    return false;
  
  Node *failedNode = this->nodeGraph.getNode(removedNodeIndex);
  if (!failedNode)
    return false;
  
  setState(NodeStatus::REPAIRING);
  
  return true;
}

bool Round::LocalNode::postMessage(const Message *msg)  {
  return false;
}

bool Round::LocalNode::waitMessage(Message *msg)  {
  return false;
}

bool Round::LocalNode::execMessage(const Message *msg) {
  return false;
}

bool Round::LocalNode::loadConfigFromString(const std::string &string, Error *error) {
  if (this->nodeConfig.loadFromString(string, error) == false)
    return false;
  return true;
}

bool Round::LocalNode::loadConfigFromFile(const std::string &filename, Error *error) {
  if (this->nodeConfig.loadFromFile(filename, error) == false)
    return false;
  return true;
}

bool Round::LocalNode::isConfigValid(Error *error) {
  return this->nodeConfig.isValid(error);
}

bool Round::LocalNode::redo(Error *error) {
  return true;
}

bool Round::LocalNode::clean(Error *error) {
  return true;
}

bool Round::LocalNode::activate(Error *error) {
  setState(NodeStatus::ACTIVATING);

  NodeGraph *nodeGraph = getNodeGraph();
  if (nodeGraph->hasNode(this) == false) {
    if (nodeGraph->addNode(this) == false)
      return false;
  }
  
  if (nodeGraph->size() <= 1)
    return true;

  setState(NodeStatus::ACTIVE);
  
  return true;
}

bool Round::LocalNode::start(Error *error) {
  stop(error);
  
  setState(NodeStatus::ACTIVATING);
  
  if (!redo(error)) {
    stop(error);
    return false;
  }
  
  if (!clean(error)) {
    stop(error);
    return false;
  }

  if (!activate(error)) {
    stop(error);
    return false;
  }

  setState(NodeStatus::ACTIVE);
  
  return true;
}

bool Round::LocalNode::stop(Error *error) {
  bool areAllOperationSucess = true;
  
  NodeGraph *nodeGraph = getNodeGraph();
  if (nodeGraph->hasNode(this) == true) {
    if (nodeGraph->removeNode(this) == false) {
      areAllOperationSucess = false;
    }
  }
  
  if (areAllOperationSucess == true) {
    setState(NodeStatus::STOP);
  }
  
  return areAllOperationSucess;
}

bool Round::LocalNode::restart(Error *error) {
  if (stop(error) == false)
    return false;
  return start(error);
}
