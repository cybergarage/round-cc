/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Log.h>
#include <round/core/RemoteNode.h>
#include <round/core/NodeGraph.h>
#include <round/core/SystemMethod.h>

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

bool Round::RemoteNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string requestAddr;
  int requestPort;
  if (!getRequestAddress(&requestAddr, error) || !getRequestPort(&requestPort, error))
    return false;

  // Set id and ts parameter
  
  clock_t localTs = incrementLocalClock();
  (const_cast<NodeRequest *>(nodeReq))->setId(localTs);
  (const_cast<NodeRequest *>(nodeReq))->setTimestamp(localTs);
  
  // HTTP Request

  uHTTP::HTTPRequest httpReq;
  httpReq.setHost(requestAddr, requestPort);
  nodeReq->toHTTPRequest(&httpReq);
  
  uHTTP::HTTPResponse httpRes;
  httpReq.post(requestAddr, requestPort, &httpRes);
  
  int statusCode = httpRes.getStatusCode();
  bool isSuccess = uHTTP::HTTP::IsStatusCodeSuccess(statusCode);
  
  std::string httpContent = httpRes.getContent();
  if (httpContent.length() <= 0)
    return isSuccess;
  
  JSONParser jsonParser;
  if (jsonParser.parse(httpContent, error) == false)
    return isSuccess;
  JSONObject *rootObj = jsonParser.getRootObject();
  if (!rootObj)
    return isSuccess;
  if (rootObj->isDictionary() == false)
    return isSuccess;
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(rootObj);
  if (!jsonDict)
    return isSuccess;

  nodeRes->set(jsonDict);

  // Update local clock
  
  clock_t remoteTs;
  if (nodeRes->getTimestamp(&remoteTs)) {
    setRemoteClock(remoteTs);
  }

  // Set error code and message
  
  if (!isSuccess) {
    nodeRes->getError(error);
    error->setCode(statusCode);
    error->setMessage(uHTTP::HTTP::StatusCodeToString(statusCode));
  }
  
  return isSuccess;
}

Round::Node *Round::RemoteNode::clone() {
  return new RemoteNode(this);
}
