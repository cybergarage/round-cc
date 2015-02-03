/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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

bool Round::ServerNode::getRequestPort(int *port, Error *error) const {
  *port = this->serverPort;
  return true;
}

bool Round::ServerNode::getRequestAddress(std::string *address, Error *error) const {
  *address = this->serverAddress;
  return true;
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
  
  if (!RPC::JSON::HTTP::IsRequestMethod(method))
    return false;
  
  if (!RPC::JSON::HTTP::IsRequestPath(uri))
    return false;

  return true;
}

Round::HttpStatusCode Round::ServerNode::postRpcRequest(uHTTP::HTTPRequest *httpReq, Message *nodeReq) {
  if (!httpReq || !nodeReq)
    return false;
  return pushMessage(nodeReq);
}

Round::HttpStatusCode Round::ServerNode::httpRpcRequestReceived(uHTTP::HTTPRequest *httpReq) {
  Error error;
  
  // Check RPC Request
  
  Message *rpcReq = NULL;
  
  if (httpReq->isPostRequest()) {
    std::string httpContent = httpReq->getContent();
    if (httpContent.length() <= 0)
      return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInvalidRequest);
    
    RoundLogTrace(httpContent.c_str());
    
    NodeRequestParser jsonParser;
    if (jsonParser.parse(httpContent, &error) == false)
      return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeParserError);
  
    JSONObject *rootObject = jsonParser.getRootObject();
    if (!rootObject) {
      return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeParserError);
    }
    
    rootObject = jsonParser.popRootObject();
    
    NodeRequest *nodeReq = dynamic_cast<NodeRequest *>(rootObject);
    if (nodeReq) {
      rpcReq = nodeReq;
    }
    else {
      NodeBatchRequest *nodeBatchReq = dynamic_cast<NodeBatchRequest *>(rootObject);
      if (nodeBatchReq) {
        rpcReq = nodeBatchReq;
      }
      else {
        delete rootObject;
      }
    }
  } else if (httpReq->isGetRequest()) {
    NodeRequest *nodeReq = NodeRequest::CreateFromHTTPGetRequest(httpReq);
    if (nodeReq) {
      rpcReq = nodeReq;
    }
  }
  
  if (!rpcReq)
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInvalidRequest);
  
  // Post RPC Request
  
  rpcReq->setHttpRequest(httpReq);
  if (!postRpcRequest(httpReq, rpcReq))
    return postRpcErrorResponse(httpReq, RPC::JSON::ErrorCodeInternalError);
  
  return uHTTP::HTTP::PROCESSING;
}
