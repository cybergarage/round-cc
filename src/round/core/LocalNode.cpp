/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <round/Round.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>
#include <round/core/local/method/SystemMethod.h>

const std::string Round::LocalNode::DEFALUT_CLUSTER = ROUNDCC_PRODUCT_NAME;

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

bool Round::LocalNode::getClusterName(std::string *name, Error *error) {
  if (this->nodeConfig.getCluster(name, error))
    return true;
  
  *name = DEFALUT_CLUSTER;
  
  return true;
}

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

bool Round::LocalNode::start(Error *error) {
  stop(error);
  
  bool areAllOperationSucess = true;
  
  setState(NodeStatus::ACTIVATING);

  nodeWorker.setObject(this);
  if (nodeWorker.start()) {
    if (!this->nodeGraph.addNode(this)) {
      areAllOperationSucess = false;
    }
  }
  else {
    areAllOperationSucess = false;
  }

  if (!areAllOperationSucess) {
    stop(error);
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
  if (!nodeGraph->clear()) {
    areAllOperationSucess = false;
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

bool Round::LocalNode::nodeAdded(Round::Node *notifyNode)  {
  Error error;
  
  std::string notifyNodeCluster;
  if (!notifyNode->getClusterName(&notifyNodeCluster, &error))
    return false;
  
  std::string thisNodeCluster;
  if (!getClusterName(&thisNodeCluster, &error))
    return false;
  
  if (thisNodeCluster.compare(notifyNodeCluster) != 0)
    return false;
  
  if (this->nodeGraph.hasNode(notifyNode))
    return true;
  
  if (!this->nodeGraph.addNode(notifyNode))
    return true;
  
  if (equals(notifyNode))
    return true;
  
  return true;
}

bool Round::LocalNode::nodeRemoved(Round::Node *notifyNode)  {
  if (!this->nodeGraph.hasNode(notifyNode))
    return true;
  
  if (equals(notifyNode)) {
    this->nodeGraph.removeNode(notifyNode);
    return true;
  }
  
  ssize_t notifyNodeIndex = this->nodeGraph.getNodeIndex(notifyNode);
  if (notifyNodeIndex < 0)
    return false;
  
  Node *failedNode = this->nodeGraph.getNode(notifyNodeIndex);
  if (!failedNode)
    return false;
  
  return true;
}

////////////////////////////////////////////////
// Method
////////////////////////////////////////////////

bool Round::LocalNode::addMethod(Method *method) {
  return this->sysMethodMgr.addMethod(method);
}

bool Round::LocalNode::setScript(const std::string &method, const std::string &lang, const std::string &code, int encodeType, Error *error) {
  return this->scriptMgr.setScript(method, lang, code, encodeType, error);
}

////////////////////////////////////////////////
// Memory
////////////////////////////////////////////////

bool Round::LocalNode::setKey(const std::string &key, const std::string &value) {
  return this->memory.setKey(key, value);
}

bool Round::LocalNode::getKey(const std::string &key, std::string *value) const {
  return this->memory.getKey(key, value);
}

////////////////////////////////////////////////
// Message
////////////////////////////////////////////////

bool Round::LocalNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter
  (const_cast<NodeRequest *>(nodeReq))->setSourceNodeParameters(this);
  
  // Post RPC message
  return execMessage(nodeReq, nodeRes, error);
}

bool Round::LocalNode::pushMessage(const Message *nodeReq) {
  return this->nodeMsgMgr.pushMessage(nodeReq);
}

bool Round::LocalNode::waitMessage(const NodeRequest **nodeReq) {
  *nodeReq = NULL;
  const Message *nodeMsg = NULL;
  if (!this->nodeMsgMgr.waitMessage(&nodeMsg))
    return false;
  *nodeReq = dynamic_cast<const NodeRequest *>(nodeMsg);
  return (*nodeReq) ? true : false;
}

////////////////////////////////////////////////
// get*Nodes
////////////////////////////////////////////////

bool Round::LocalNode::getQuorumNodes(NodeList *nodes, size_t quorum) {
  NodeGraph *nodeGraph = getNodeGraph();
  if (!nodeGraph)
    return false;
  
  for (size_t n=1; n<=quorum; n++) {
    Node *node = nodeGraph->getOffsetNode(this, n);
    if (!node)
      continue;
    if (node->equals(this))
      continue;
    RemoteNode *remoteNode = new RemoteNode(node);
    remoteNode->setWeakFlag(false);
    nodes->addNode(remoteNode);
  }
  
  return true;
}

bool Round::LocalNode::getAllOtherNodes(NodeList *nodes) {
  NodeGraph *nodeGraph = getNodeGraph();
  if (!nodeGraph)
    return false;
  
  nodeGraph->lock();
  
  for (NodeGraph::iterator nodeIt = nodeGraph->begin(); nodeIt != nodeGraph->end(); nodeIt++) {
    Node *node = dynamic_cast<Node *>(*nodeIt);
    if (!node)
      continue;
    if (node->equals(this))
      continue;
    RemoteNode *remoteNode = new RemoteNode(node);
    remoteNode->setWeakFlag(false);
    nodes->addNode(remoteNode);
  }
  
  nodeGraph->unlock();

  return true;
}

////////////////////////////////////////////////
// Execution
////////////////////////////////////////////////

bool Round::LocalNode::setError(int rpcErrorCode, Error *err) {
  if (!err)
    return false;
  RPC::JSON::ErrorCodeToError(rpcErrorCode, err);
  return true;
}

bool Round::LocalNode::execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  if (!nodeReq || !nodeRes || !error)
    return false;
  
  // Check dest
  
  if (!nodeReq->isDestValid()) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
    return false;
  }
  
  bool isDestHash = nodeReq->isDestHash();
  if (isDestHash) {
    std::string nodeHash;
    if (nodeReq->getDest(&nodeHash)) {
      NodeGraph *nodeGraph = getNodeGraph();
      if (!nodeGraph->isHandleNode(this, nodeHash)) {
        setError(RPC::JSON::ErrorCodeMovedPermanently, error);
        return false;
      }
    }
  }
  
  // Update local clock
  
  clock_t remoteTs;
  if (nodeRes->getTimestamp(&remoteTs)) {
    setRemoteClock(remoteTs);
  }
  else {
    incrementLocalClock();
  }
  
  // Exec Method (One node)

  bool isDestOne = nodeReq->isDestOne();
  if (isDestOne) {
    return execMethod(nodeReq, nodeRes, error);
  }
  
  // Exec Method (Multi node)

  JSONArray *batchArray = new JSONArray();
  nodeRes->setResult(batchArray);
  
  Error thisNodeError;
  NodeResponse *thisNodeRes = new NodeResponse();
  execMethod(nodeReq, thisNodeRes, &thisNodeError);
  thisNodeRes->setDest(this);
  batchArray->add(thisNodeRes);
  
  NodeList otherNodes;
  if (nodeReq->isDestAll()) {
    getAllOtherNodes(&otherNodes);
  }
  else if (nodeReq->hasQuorum()) {
    size_t quorum;
    if (nodeReq->getQuorum(&quorum)) {
      getQuorumNodes(&otherNodes, quorum);
    }
  }
  for (NodeList::iterator node = otherNodes.begin(); node != otherNodes.end(); node++) {
    Error otherNodeError;
    NodeResponse *otherNodeRes = new NodeResponse();
    (*node)->postMessage(nodeReq, otherNodeRes, &otherNodeError);
    otherNodeRes->setDest((*node));
    batchArray->add(otherNodeRes);
  }

  return true;
}

////////////////////////////////////////////////
// Dynamic Method
////////////////////////////////////////////////

bool Round::LocalNode::isDynamicMethod(const std::string &method) {
  return this->scriptMgr.hasScript(method);
}

bool Round::LocalNode::execDynamicMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string method;
  nodeReq->getMethod(&method);
  
  if (!this->scriptMgr.hasScript(method)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  std::string params;
  nodeReq->getParams(&params);
  
  std::string result;
  bool isSuccess = this->scriptMgr.run(method, params, &result, error);
  if (isSuccess) {
    nodeRes->setResult(result);
  }
  else {
    nodeRes->setError(error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Static Method
////////////////////////////////////////////////

bool Round::LocalNode::isStaticMethod(const std::string &method) {
  return this->staticMethodMgr.hasMethod(method);
}

bool Round::LocalNode::execStaticMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (!this->staticMethodMgr.hasMethod(reqMethod)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  bool isSuccess = this->staticMethodMgr.exec(reqMethod, this, nodeReq, nodeRes);
  if (!isSuccess) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Native Method
////////////////////////////////////////////////

bool Round::LocalNode::isNativeMethod(const std::string &method) {
  return this->sysMethodMgr.hasMethod(method);
}

bool Round::LocalNode::execNativeMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (!this->sysMethodMgr.hasMethod(reqMethod)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  bool isSuccess = this->sysMethodMgr.exec(reqMethod, this, nodeReq, nodeRes);
  if (!isSuccess) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Exce Method
////////////////////////////////////////////////

bool Round::LocalNode::execMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter
  
  size_t msgId;
  if (nodeReq->getId(&msgId)) {
    nodeRes->setId(msgId);
  }
  nodeRes->setTimestamp(getLocalClock());
  
  // Exec Message
  
  std::string name;
  if (!nodeReq->getMethod(&name) || (name.length() <= 0)) {
    setError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  if (isStaticMethod(name)) {
    return execStaticMethod(nodeReq, nodeRes, error);
  }
  
  if (isDynamicMethod(name)) {
    return execDynamicMethod(nodeReq, nodeRes, error);
  }
  
  if (isNativeMethod(name)) {
    return execNativeMethod(nodeReq, nodeRes, error);
  }
  
  setError(RPC::JSON::ErrorCodeMethodNotFound, error);
  
  return false;
}
