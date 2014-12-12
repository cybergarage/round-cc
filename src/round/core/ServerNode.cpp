/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/ServerNode.h>
#include <round/core/HTTP.h>
#include <round/core/impl/UPnPServerNode.h>
#include <round/common/StringTokenizer.h>
#include <round/core/Log.h>

Round::ServerNode::ServerNode() {
}

Round::ServerNode::~ServerNode() {
}

bool Round::ServerNode::getVersion(std::string *buffer, Error *error) const {
  *buffer = VER.c_str();
  return true;
}

bool Round::ServerNode::start(Error *error) {
  if (LocalNode::start(error) == false)
    return false;

  return true;
}

bool Round::ServerNode::stop(Error *error) {
  bool isSuccess = true;

  if (LocalNode::stop(error) == false)
    isSuccess = false;

  return isSuccess;
}

Round::HttpStatusCode Round::ServerNode::postRpcErrorResponse(uHTTP::HTTPRequest *httpReq, int rpcErrorCode) {
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(RPC::JSON::HTTP::ErrorCodeToHTTPStatusCode(rpcErrorCode));
  return httpReq->post(&httpRes);
}

bool Round::ServerNode::isRpcRequest(uHTTP::HTTPRequest *httpReq) {
  std::string method;
  httpReq->getMethod(method);
  std::string uri;
  httpReq->getURI(uri);
  
  if (method.compare(RPC::HTTP::METHOD) == 0) {
    if (uri.compare(RPC::HTTP::ENDPOINT) == 0)
      return true;
  }

  return false;
}

Round::HttpStatusCode Round::ServerNode::postRpcRequest(uHTTP::HTTPRequest *httpReq, NodeRequest *nodeReq) {
  if (!httpReq || !nodeReq)
    return false;
  nodeReq->setHttpRequest(httpReq);
  return pushMessage(nodeReq);
}

Round::HttpStatusCode Round::ServerNode::httpRpcRequestReceived(uHTTP::HTTPRequest *httpReq) {
  
  // Check RPC Request

  std::string httpContent = httpReq->getContent();
  if (httpContent.length() <= 0)
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInvalidRequest);
  
  NodeRequestParser jsonParser;
  if (jsonParser.parse(httpContent) == false)
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeParserError);
  
  if (jsonParser.getObject()->isDictionary() == false)
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInvalidRequest);

  NodeRequest *nodeReq = dynamic_cast<NodeRequest *>(jsonParser.getObject());
  if (!nodeReq)
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInvalidRequest);

  // Post RPC Request
  
  if (!postRpcRequest(httpReq, nodeReq))
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInternalError);
  
  return uHTTP::HTTP::PROCESSING;
}
