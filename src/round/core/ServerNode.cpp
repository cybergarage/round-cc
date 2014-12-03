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

const std::string Round::ServerNode::HTTP_JSON_RPC_ENTRYPOINT  = "/rpc/do";
const std::string Round::ServerNode::HTTP_JSON_RPC_CONTENTTYPE = "application/json-rpc";

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

Round::HttpStatusCode Round::ServerNode::httpBadRpcRequestRecieved(uHTTP::HTTPRequest *httpReq, int rpcErrorCode) {
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(RPC::JSON::HTTP::JSONDetailStatus2HTTPStatus(rpcErrorCode));
  return httpReq->post(&httpRes);
}

bool Round::ServerNode::isNodeRpcRequest(uHTTP::HTTPRequest *httpReq) {
  std::string method;
  httpReq->getMethod(method);
  std::string uri;
  httpReq->getURI(uri);
  
  if (method.compare("PUT") == 0) {
    if (uri.compare(HTTP_JSON_RPC_ENTRYPOINT) == 0)
      return true;
  }
  return false;
}

Round::HttpStatusCode Round::ServerNode::httpNodeRpcRequestReceived(uHTTP::HTTPRequest *httpReq) {
  std::string httpContent = httpReq->getContent();
  if (httpContent.length() <= 0)
    return httpBadRpcRequestRecieved(httpReq, RPC::JSON::DetailStatusInvalidRequest);
  
  JSONParser jsonParser;
  if (jsonParser.parse(httpContent) == false)
    return httpBadRpcRequestRecieved(httpReq, RPC::JSON::DetailStatusParserError);
  
  if (jsonParser.getObject()->isDictionary() == false)
    return httpBadRpcRequestRecieved(httpReq, RPC::JSON::DetailStatusInvalidRequest);
  
  JSONDictionary *reqDict = static_cast<JSONDictionary *>(jsonParser.getObject());
  if (!reqDict)
    return httpBadRpcRequestRecieved(httpReq, RPC::JSON::DetailStatusInvalidRequest);

  return uHTTP::HTTP::BAD_REQUEST;
}

