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

Round::LocalNodeWorkder::LocalNodeWorkder() {
}

Round::LocalNodeWorkder::~LocalNodeWorkder() {
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

    NodeResponse nodeResLocal;
    NodeResponse *nodeRes = nodeReq->getResponse();
    if (!nodeRes) {
      nodeRes = &nodeResLocal;
    }
    
    Error err;
    node->execMessage(nodeReq, nodeRes, &err);

    uHTTP::HTTPRequest *httpRes = nodeReq->getHttpRequest();
    if (httpRes) {
      post(nodeRes, httpRes);
    }
    
    delete nodeReq;
  }
}

void Round::LocalNodeWorkder::post(const NodeResponse *nodeRes, uHTTP::HTTPRequest *httpReq) {
  uHTTP::HTTPResponse httpRes;
  nodeRes->toHTTPResponse(&httpRes);
  httpReq->post(&httpRes);
}
