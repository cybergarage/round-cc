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
#include <round/core/SystemMethod.h>

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
// Message
////////////////////////////////////////////////

bool Round::LocalNode::postMessage(NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter
  
  clock_t localTs = getLocalClock();
  nodeReq->setId(localTs);
  nodeReq->setTimestamp(localTs);
  
  // Post RPC message
  
  return execMessage(nodeReq, nodeRes, error);
}

bool Round::LocalNode::pushMessage(const NodeRequest *nodeReq) {
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
// Execution
////////////////////////////////////////////////

bool Round::LocalNode::hasUserMethod(const std::string &method) {
  return this->scriptMgr.hasScript(method);
}

bool Round::LocalNode::setError(int rpcErrorCode, Error *err) {
  if (!err)
    return false;
  RPC::JSON::ErrorCodeToError(rpcErrorCode, err);
  return true;
}

bool Round::LocalNode::execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  if (!nodeReq || !nodeRes || !err)
    return false;
  
  // Check hash code
  
  if (nodeReq->hasHash()) {
    std::string hashCode;
    if (nodeReq->getHash(&hashCode)) {
      if (hashCode.length() != HashObject::GetHashCodeLength()) {
        setError(RPC::JSON::ErrorCodeBadHashCode, err);
        return false;
      }
      NodeGraph *nodeGraph = getNodeGraph();
      if (!nodeGraph->isHandleNode(this, hashCode)) {
        setError(RPC::JSON::ErrorCodeMovedPermanently, err);
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
  
  // Set id and ts parameter
  
  size_t msgId;
  if (nodeReq->getId(&msgId)) {
    nodeRes->setId(msgId);
  }
  nodeRes->setTimestamp(getLocalClock());

  // Exec Message
  
  std::string name;
  if (!nodeReq->getMethod(&name) || (name.length() <= 0)) {
    setError(RPC::JSON::ErrorCodeMethodNotFound, err);
    return false;
  }
  
  if (isSetMethod(name)) {
    if (!setMethod(nodeReq, nodeRes, err)) {
      setError(RPC::JSON::ErrorCodeInvalidParams, err);
      return false;
    }
    return true;
  }

  if (hasUserMethod(name)) {
    std::string params;
    nodeReq->getParams(&params);
    std::string result;
    bool isSuccess = this->scriptMgr.run(name, params, &result, err);
    if (isSuccess) {
      nodeRes->setResult(result);
    }
    else {
      nodeRes->setError(err);
    }
    return isSuccess;
  }
  
  if (isSystemMethod(name)) {
    return execSystemMethod(nodeReq, nodeRes, err);
  }
  
  setError(RPC::JSON::ErrorCodeMethodNotFound, err);
  
  return false;
}

////////////////////////////////////////////////
// System Static Method
////////////////////////////////////////////////

bool Round::LocalNode::isSetMethod(const std::string &method) {
  return (SystemMethodRequest::SET_METHOD.compare(method) == 0) ? true : false;
}

bool Round::LocalNode::setMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
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

  // Couldn't override '_set_method'
  if (isSetMethod(scriptMethod)) {
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

////////////////////////////////////////////////
// System Dynamic Method
////////////////////////////////////////////////

bool Round::LocalNode::isSystemMethod(const std::string &method) {
  return (method.find(SystemMethodRequest::PREFIX) == 0) ? true : false;
}

bool Round::LocalNode::execSystemMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  static std::map<std::string, int> systemMethods;
  enum {
      SystemGetNodeInfo,
      SystemGetClusterInfo,
      SystemGetNetworkInfo,
  };
  
  if (systemMethods.size() <= 0) {
    systemMethods[SystemMethodRequest::GET_NODE_INFO] = SystemGetNodeInfo;
    systemMethods[SystemMethodRequest::GET_CLUSTER_INFO] = SystemGetClusterInfo;
    systemMethods[SystemMethodRequest::GET_NETWORK_INFO] = SystemGetNetworkInfo;
  }
  
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (systemMethods.find(reqMethod) == systemMethods.end()) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  int systemMethodType = systemMethods[reqMethod];
  switch (systemMethodType) {
  case SystemGetNodeInfo:
    return _get_node_info(nodeReq, nodeRes, error);
  case SystemGetClusterInfo:
    return _get_cluster_info(nodeReq, nodeRes, error);
  case SystemGetNetworkInfo:
    return _get_network_info(nodeReq, nodeRes, error);
  }
  
  RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);

  return false;
}

bool Round::LocalNode::_get_node_info(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  SystemGetNodeInfoResponse sysRes(nodeRes);
  return sysRes.setNode(this);
}

bool Round::LocalNode::_get_cluster_info(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  return sysRes.setCluster(this);
}

bool Round::LocalNode::_get_network_info(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  SystemGetNetworkInfoResponse sysRes(nodeRes);
  return sysRes.setClusters(this);
}
