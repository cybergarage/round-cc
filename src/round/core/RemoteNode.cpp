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

Round::RemoteNode::RemoteNode(const Round::Node *node) {
  Error err;
  node->getRequestAddress(&this->requestAddress, &err);
  node->getRequestPort(&this->requestPort, &err);
}

Round::RemoteNode::RemoteNode(const std::string &address, int port) {
  this->requestAddress = address;
  this->requestPort = port;
}

Round::RemoteNode::~RemoteNode() {
}

bool Round::RemoteNode::getRequestPort(int *port, Error *error) const {
  *port = this->requestPort;
  return true;
}

bool Round::RemoteNode::getRequestAddress(std::string *address, Error *error) const {
  *address = this->requestAddress;
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
  if (jsonParser.parse(httpContent) == false)
    return isSuccess;
  if (jsonParser.getObject()->isDictionary() == false)
    return isSuccess;
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getObject());
  if (!jsonDict)
    return isSuccess;

  nodeRes->set(jsonDict);

  if (!isSuccess) {
    nodeRes->getError(error);
    error->setCode(statusCode);
    error->setMessage(uHTTP::HTTP::StatusCodeToString(statusCode));
  }
  
  return isSuccess;
}

Round::Node *Round::RemoteNode::clone() const {
  return new RemoteNode(this);
}
