/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Log.h>
#include <round/core/RemoteNode.h>
#include <round/core/NodeGraph.h>
#include <round/core/Method.h>
#include <round/core/local/method/SystemMethod.h>

#include <uhttp/net/Socket.h>

Round::RemoteNode::RemoteNode() {
  setRequestAddress("");
  setRequestPort(-1);
  setClusterName("");
}

Round::RemoteNode::RemoteNode(Round::Node *node) {
  Error err;
  node->getRequestAddress(&this->requestAddress, &err);
  node->getRequestPort(&this->requestPort, &err);
  if (hasClusterName()) {
    node->getClusterName(&this->clusterName, &err);
  }
}

Round::RemoteNode::RemoteNode(const std::string &address, int port) {
  setRequestAddress(address);
  setRequestPort(port);
  setClusterName("");
}

Round::RemoteNode::~RemoteNode() {
}

bool Round::RemoteNode::setRequestAddress(const std::string &address) {
  this->requestAddress = address;
  return true;
}

bool Round::RemoteNode::setRequestPort(int port) {
  this->requestPort = port;
  return true;
}

bool Round::RemoteNode::setClusterName(const std::string &name) {
  this->clusterName = name;
  return true;
}

bool Round::RemoteNode::getRequestAddress(std::string *address, Error *error) const {
  if (this->requestAddress.length() <= 0)
    return false;
  *address = this->requestAddress;
  return true;
}

bool Round::RemoteNode::getRequestPort(int *port, Error *error) const {
  if (this->requestPort < 0)
    return false;
  *port = this->requestPort;
  return true;
}

bool Round::RemoteNode::getClusterName(std::string *name, Error *error) {
  if (this->clusterName.length() <= 0) {
    SystemGetNodeInfoRequest nodeReq;
    NodeResponse nodeRes;
    if (!postMessage(&nodeReq, &nodeRes, error))
      return false;
    
    SystemGetNodeInfoResponse sysRes(&nodeRes);
    if (!sysRes.getCluster(&this->clusterName))
      return false;
  }
  
  *name = this->clusterName;
  return true;
}

bool Round::RemoteNode::setUpdatedNodeStatusParameters(const NodeRequest *nodeReq) {
  if (!nodeReq)
    return false;
  
  // Set id and ts parameter
  
  lock();
  
  incrementLocalClock();
  (const_cast<NodeRequest *>(nodeReq))->setSourceNodeParameters(this);
  
  unlock();
  
  return true;
}

bool Round::RemoteNode::postMessage(uHTTP::HTTPRequest *httpReq, JSONObject **rootObj, Error *error) {
  // HTTP Request
  
  std::string requestAddr;
  int requestPort;
  if (!getRequestAddress(&requestAddr, error) || !getRequestPort(&requestPort, error))
    return false;
  
  httpReq->setHost(requestAddr, requestPort);
  
  uHTTP::HTTPResponse httpRes;
  httpReq->post(requestAddr, requestPort, &httpRes);
  
  // Set error code and message
  
  int statusCode = httpRes.getStatusCode();
  if (!uHTTP::HTTP::IsStatusCodeSuccess(statusCode)) {
    error->setCode(statusCode);
    error->setMessage(uHTTP::HTTP::StatusCodeToString(statusCode));
    return false;
  }
  
  std::string httpContent = httpRes.getContent();
  if (httpContent.length() <= 0) {
    statusCode = uHTTP::HTTP::NOT_FOUND;
    error->setCode(statusCode);
    error->setMessage(uHTTP::HTTP::StatusCodeToString(statusCode));
    return false;
  }
  
  JSONParser jsonParser;
  if (jsonParser.parse(httpContent, error) == false) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }
  
  *rootObj = jsonParser.popRootObject();
  if (!(*rootObj)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }

  return true;
}

bool Round::RemoteNode::postMessage(uHTTP::HTTPRequest *httpReq, NodeResponse *nodeRes, Error *error) {
  // HTTP Request
  
  JSONObject *rootObj = NULL;
  if (!postMessage(httpReq, &rootObj, error))
    return false;
  
  if (!rootObj->isDictionary()) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(rootObj);
  if (!jsonDict) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }
  
  nodeRes->set(jsonDict);
  
  // Update local clock
  
  clock_t remoteTs;
  if (nodeRes->getTimestamp(&remoteTs)) {
    setRemoteClock(remoteTs);
  }
  
  return true;
}

bool Round::RemoteNode::postMessage(uHTTP::HTTPRequest *httpReq, NodeBatchResponse *nodeBatchRes, Error *error) {
  // HTTP Request
  
  JSONObject *rootObj = NULL;
  if (!postMessage(httpReq, &rootObj, error))
    return false;
  
  if (!rootObj->isArray()) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }
  
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(rootObj);
  if (!jsonArray) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeParserError, error);
    return false;
  }
  
  nodeBatchRes->set(jsonArray);
  
  // Update local clock

  for (NodeBatchResponse::iterator jsonObj = nodeBatchRes->begin(); jsonObj != nodeBatchRes->end(); jsonObj++) {
    JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(*jsonObj);
    if (!jsonDict)
      continue;
    NodeResponse nodeRes;
    nodeRes.set(jsonDict);
    clock_t remoteTs;
    if (!nodeRes.getTimestamp(&remoteTs))
      continue;
    setRemoteClock(remoteTs);
  }
    
  return true;
}

bool Round::RemoteNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter

  if (!setUpdatedNodeStatusParameters(nodeReq))
    return false;
  
  // HTTP Request

  uHTTP::HTTPRequest httpReq;
  nodeReq->toHTTPPostRequest(&httpReq);

  return postMessage(&httpReq, nodeRes, error);
}

bool Round::RemoteNode::postMessage(const NodeBatchRequest *nodeBatchReq, NodeBatchResponse *nodeBatchRes, Error *error) {
  // Set id and ts parameter
  
  for (NodeBatchRequest::const_iterator jsonObj = nodeBatchReq->begin(); jsonObj != nodeBatchReq->end(); jsonObj++) {
    const NodeRequest *nodeReq = dynamic_cast<const NodeRequest *>(*jsonObj);
    if (!nodeReq)
      continue;
    setUpdatedNodeStatusParameters(nodeReq);
  }
  
  // HTTP Request
  
  uHTTP::HTTPRequest httpReq;
  nodeBatchReq->toHTTPPostRequest(&httpReq);
  
  return postMessage(&httpReq, nodeBatchRes, error);
}

bool Round::RemoteNode::getMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error, bool jsonRpcEncodeEnable) {
  // Set id and ts parameter
  
  if (!setUpdatedNodeStatusParameters(nodeReq))
    return false;
  
  // HTTP Request
  
  uHTTP::HTTPRequest httpReq;
  nodeReq->toHTTPGetRequest(&httpReq, jsonRpcEncodeEnable);
  
  return postMessage(&httpReq, nodeRes, error);
}

Round::Node *Round::RemoteNode::clone() {
  return new RemoteNode(this);
}
