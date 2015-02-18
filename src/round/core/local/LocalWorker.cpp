/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>
#include <round/core/Log.h>

Round::LocalWorkder::LocalWorkder() {
}

Round::LocalWorkder::~LocalWorkder() {
}

void Round::LocalWorkder::post(uHTTP::HTTPRequest *httpReq, const NodeResponse *nodeRes) {
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

void Round::LocalWorkder::run() {
  LocalNode *node = getObject();
  if (!node)
    return;
  
  while (isRunnable()) {
    const Message *nodeMsg;
    if (!node->waitMessage(&nodeMsg))
      break;
    
    if (!nodeMsg)
      break;

    const NodeRequest *nodeReq = dynamic_cast<const NodeRequest *>(nodeMsg);
    if (nodeReq) {
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
      
      continue;
    }
    
    const NodeBatchRequest *nodeBatchReq = dynamic_cast<const NodeBatchRequest *>(nodeMsg);
    if (nodeBatchReq) {
      std::string reqStr;
      nodeBatchReq->toJSONString(&reqStr);
      RoundLogTrace(reqStr.c_str());
      
      Error err;
      NodeBatchResponse nodeBatchRes;
      node->execMessage(nodeBatchReq, &nodeBatchRes, &err);
      
      std::string resStr;
      nodeBatchRes.toJSONString(&resStr);
      RoundLogTrace(resStr.c_str());
      
      uHTTP::HTTPRequest *httpReq = nodeReq->getHttpRequest();
      if (httpReq) {
        post(httpReq, &nodeBatchRes);
      }
      
      delete nodeReq;
      
      continue;
    }
    
    delete nodeMsg;
  }
}
