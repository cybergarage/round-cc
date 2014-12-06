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

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::LocalNode::LocalNode() {
  init();
}

Round::LocalNode::~LocalNode() {
}

void Round::LocalNode::init() {
  setState(NodeStatus::STOP);
}

////////////////////////////////////////////////
// Configuration
////////////////////////////////////////////////

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

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

bool Round::LocalNode::start(Error *error) {
  stop(error);
  
  setState(NodeStatus::ACTIVATING);

  nodeWorker.setObject(this);
  if (!nodeWorker.start()) {
    setState(NodeStatus::STOP);
    return false;
  }
  
  setState(NodeStatus::ACTIVE);
  
  return true;
}

bool Round::LocalNode::stop(Error *error) {
  bool areAllOperationSucess = true;
  
  if (!nodeWorker.stop()) {
    areAllOperationSucess = false;
    return false;
  }
  
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

////////////////////////////////////////////////
// Notification
////////////////////////////////////////////////

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
  
  return true;
}

////////////////////////////////////////////////
// Message
////////////////////////////////////////////////

bool Round::LocalNode::postMessage(const NodeRequest *reqMsg, NodeResponse *resMsg) {
}

bool Round::LocalNode::pushMessage(const NodeRequest *nodeReq) {
  return this->nodeMsgMgr.pushMessage(nodeReq);
}

bool Round::LocalNode::waitMessage(const NodeRequest **nodeReq) {
  const Message *nodeMsg = dynamic_cast<const Message *>(*nodeReq);
  if (!nodeMsg)
    return false;
  return this->nodeMsgMgr.waitMessage(&nodeMsg);
}

////////////////////////////////////////////////
// Execution
////////////////////////////////////////////////

bool Round::LocalNode::execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  if (!nodeRes || !nodeRes || !err)
    return false;

  ScriptName name;
  nodeReq->getMethod(&name);

  ScriptParams params;
  nodeReq->getMethod(&params);
  
  ScriptResults result;
  
  return this->scriptMgr.run(name, params, &result, err);
}
