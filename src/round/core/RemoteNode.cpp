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

#include <uhttp/net/Socket.h>

Round::RemoteNode::RemoteNode(const Round::Node *node) {
  this->requestAddress = node->getRequestAddress();
  this->requestPort = node->getRequestPort();
}

Round::RemoteNode::RemoteNode(const std::string &address, int port) {
  this->requestAddress = address;
  this->requestPort = port;
}

Round::RemoteNode::~RemoteNode() {
}

bool Round::RemoteNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  uHTTP::HTTPRequest httpReq;
  httpReq.setHost(getRequestAddress(), getRequestPort());
  nodeReq->toHTTPRequest(&httpReq);
  
  uHTTP::HTTPResponse httpRes;
  httpReq.post(getRequestAddress(), getRequestPort(), &httpRes);
  
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

  nodeRes->getError(error);
  error->setCode(statusCode);
  error->setMessage(uHTTP::HTTP::StatusCodeToString(statusCode));
  
  return isSuccess;
}

Round::Node *Round::RemoteNode::clone() const {
  return new RemoteNode(this);
}
