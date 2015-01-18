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
#include <round/core/method/SystemMethod.h>

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
  return this->nodeConfig.getCluster(name, error);
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
  
  // Check hash code
  
  if (nodeReq->hasHash()) {
    std::string hashCode;
    if (nodeReq->getHash(&hashCode)) {
      if (hashCode.length() != HashObject::GetHashCodeLength()) {
        setError(RPC::JSON::ErrorCodeBadHashCode, error);
        return false;
      }
      NodeGraph *nodeGraph = getNodeGraph();
      if (!nodeGraph->isHandleNode(this, hashCode)) {
        setError(RPC::JSON::ErrorCodeMovedPermanently, error);
        return false;
      }
    }
  }
  
  // Check dest
  
  bool isDestOne = true;
  if (nodeReq->hasDest()) {
    isDestOne = nodeReq->isDestOne();
    if (!isDestOne && !nodeReq->isDestValid()) {
      setError(RPC::JSON::ErrorCodeInvalidParams, error);
      return false;
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
  
  if (isDestOne) {
    return execMethod(nodeReq, nodeRes, error);
  }
  
  // Exec Method (Multi node)

  JSONArray *batchArray = new JSONArray();
  nodeRes->setResult(batchArray);
  
  Error thisNodeError;
  NodeResponse *thisNodeRes = new NodeResponse();
  execMethod(nodeReq, thisNodeRes, &thisNodeError);
  thisNodeRes->setHash(this);
  batchArray->add(thisNodeRes);
  
  NodeList otherNodes;
  if (nodeReq->isDestAll()) {
    getAllOtherNodes(&otherNodes);
  }
  else if (nodeReq->isDestQuorum()) {
    size_t quorum;
    if (nodeReq->getQuorum(&quorum)) {
      getQuorumNodes(&otherNodes, quorum);
    }
  }
  for (NodeList::iterator node = otherNodes.begin(); node != otherNodes.end(); node++) {
    Error otherNodeError;
    NodeResponse *otherNodeRes = new NodeResponse();
    (*node)->postMessage(nodeReq, otherNodeRes, &otherNodeError);
    otherNodeRes->setHash((*node));
    batchArray->add(otherNodeRes);
  }

  return true;
}

////////////////////////////////////////////////
// Dynamic Method
////////////////////////////////////////////////

bool Round::LocalNode::hasDynamicMethod(const std::string &method) {
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
// Native Method
////////////////////////////////////////////////

bool Round::LocalNode::hasNativeMethod(const std::string &method) {
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
  
  if (is_set_method(name)) {
    if (!set_method(nodeReq, nodeRes, error)) {
      setError(RPC::JSON::ErrorCodeInvalidParams, error);
      return false;
    }
    return true;
  }
  
  if (hasDynamicMethod(name)) {
    return execDynamicMethod(nodeReq, nodeRes, error);
  }
  
  if (hasNativeMethod(name)) {
    return execNativeMethod(nodeReq, nodeRes, error);
  }
  
  setError(RPC::JSON::ErrorCodeMethodNotFound, error);
  
  return false;
}

////////////////////////////////////////////////
// set_method
////////////////////////////////////////////////

bool Round::LocalNode::is_set_method(const std::string &method) {
  return (SystemMethod::SET_METHOD.compare(method) == 0) ? true : false;
}

bool Round::LocalNode::set_method(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  std::string params;
  nodeReq->getParams(&params);
  
  JSONParser jsonParser;
  if (!jsonParser.parse(params, err)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }
  
  JSONObject *jsonObj = jsonParser.getRootObject();
  if (!jsonObj->isDictionary()) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }

  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (!jsonDict) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }
  
  std::string scriptMethod;
  if (!jsonDict->get(SystemMethodRequest::NAME, &scriptMethod) || (scriptMethod.length() <= 0)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }

  // Couldn't override 'set_method'
  if (is_set_method(scriptMethod)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }

  std::string scriptLang;
  if (!jsonDict->get(SystemMethodRequest::LANGUAGE, &scriptLang) || (scriptLang.length() <= 0)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    return false;
  }

  // This method is removed if the code parameter is null.
  std::string scriptCode;
  jsonDict->get(SystemMethodRequest::CODE, &scriptCode);
  
  // Encode
  int encodeType = Script::ENCODING_NONE;
  std::string encodeTypeStr;
  if (jsonDict->get(SystemMethodRequest::ENCODE, &encodeTypeStr)) {
    if (encodeTypeStr.compare(SystemMethodRequest::ENCODE_BASE64)) {
      encodeType = Script::ENCODING_BASE64;
    }
  }
  
  return this->scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, encodeType, err);
}
