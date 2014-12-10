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

bool Round::LocalNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  return execMessage(nodeReq, nodeRes, error);
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

bool Round::LocalNode::hasUserMethod(const std::string &method) {
  return this->scriptMgr.hasScript(method);
}

bool Round::LocalNode::execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  if (!nodeRes || !nodeRes || !err)
    return false;
  
  ScriptName name;
  nodeReq->getMethod(&name);
  
  if (isSetMethod(name)) {
    if (!setMethod(nodeReq, nodeRes, err)) {
      int errCode = RPC::JSON::ErrorCodeInvalidParams;
      err->setCode(errCode);
      err->setMessage(RPC::JSON::ErrorCodeToString(errCode));
      return false;
    }
    return true;
  }

  if (hasUserMethod(name)) {
    ScriptParams params;
    nodeReq->getParams(&params);
    ScriptResults result;
    return this->scriptMgr.run(name, params, &result, err);
  }
  
  if (isSystemMethod(name)) {
    return execSystemMethod(nodeReq, nodeRes, err);
  }
  
  RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, err);
  return false;
}

////////////////////////////////////////////////
// System Static Method
////////////////////////////////////////////////

bool Round::LocalNode::isSetMethod(const std::string &method) {
  
  return (SystemMethodRequest::SET_METHOD.compare(method) == 0) ? true : false;
}

bool Round::LocalNode::setMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *err) {
  ScriptParams params;
  nodeReq->getParams(&params);
  
  JSONParser jsonParser;
  if (!jsonParser.parse(params)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }
  
  JSONObject *jsonObj = jsonParser.getObject();
  if (!jsonObj->isDictionary()) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }

  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (!jsonDict) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }
  
  std::string scriptMethod;
  if (!jsonDict->get(SystemMethodRequest::NAME, &scriptMethod) || (scriptMethod.length() <= 0)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }

  // Couldn't override '_set_method'
  if (isSetMethod(scriptMethod)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }

  std::string scriptLang;
  if (!jsonDict->get(SystemMethodRequest::LANGUAGE, &scriptLang) || (scriptLang.length() <= 0)) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeInvalidParams, err);
    return false;
  }

  // This method is removed if the code parameter is null.
  std::string scriptCode;
  jsonDict->get(SystemMethodRequest::CODE, &scriptCode);
  
  return this->scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, err);
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
      SystemGetClusterList,
  };
  
  if (systemMethods.size() <= 0) {
    systemMethods[SystemMethodRequest::GET_NODE_INFO] = SystemGetNodeInfo;
    systemMethods[SystemMethodRequest::GET_CLUSTER_INFO] = SystemGetClusterInfo;
    systemMethods[SystemMethodRequest::GET_CLUSTER_LIST] = SystemGetClusterList;
  }
  
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (systemMethods.find(reqMethod) == systemMethods.end()) {
    RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, error);
    return false;
  }
  
  int systemMethodType = systemMethods[reqMethod];
  switch (systemMethodType) {
  case SystemGetNodeInfo:
    return getNodeInfo(nodeReq, nodeRes, error);
  case SystemGetClusterInfo:
    return getClusterInfo(nodeReq, nodeRes, error);
  case SystemGetClusterList:
    return getClusterList(nodeReq, nodeRes, error);
  }
  
  RPC::JSON::ErrorCodeToError(ScriptManagerErrorCodeMethodNotFound, error);

  return false;
}

bool Round::LocalNode::getNodeInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  return false;
}

bool Round::LocalNode::getClusterInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  return false;
}

bool Round::LocalNode::getClusterList(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  return false;
}
