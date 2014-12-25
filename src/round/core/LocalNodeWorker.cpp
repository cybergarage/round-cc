/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>
#include <round/core/Log.h>

Round::LocalNodeWorkder::LocalNodeWorkder() {
}

Round::LocalNodeWorkder::~LocalNodeWorkder() {
}

void Round::LocalNodeWorkder::post(uHTTP::HTTPRequest *httpReq, const NodeResponse *nodeRes) {
  int statusCode = uHTTP::HTTP::OK_REQUEST;
  Error err;
  if (nodeRes->getError(&err)) {
    statusCode = RPC::JSON::HTTP::ErrorCodeToHTTPStatusCode(err.getDetailCode());
  }
  
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(statusCode);
  nodeRes->toHTTPResponse(&httpRes);
  
  httpReq->post(&httpRes);
}

void Round::LocalNodeWorkder::run() {
  LocalNode *node = getObject();
  if (!node)
    return;
  
  while (isRunnable()) {
    const NodeRequest *nodeReq;
    if (!node->waitMessage(&nodeReq))
      break;
    
    if (!nodeReq)
      break;

    std::string reqStr;
    nodeReq->toJSONString(&reqStr);
    RoundLogTrace(reqStr.c_str());
    
    NodeResponse nodeRes;
    nodeRes.setVersion(RPC::JSON::VER);
    
    Error err;
    
    if (!node->execMessage(nodeReq, &nodeRes, &err)) {
      nodeRes.setError(&err);
    }
    
    std::string resStr;
    nodeRes.toJSONString(&resStr);
    RoundLogTrace(resStr.c_str());

    uHTTP::HTTPRequest *httpReq = nodeReq->getHttpRequest();
    if (httpReq) {
      post(httpReq, &nodeRes);
    }
    
    delete nodeReq;
  }
}
