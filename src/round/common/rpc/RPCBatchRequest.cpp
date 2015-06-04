/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/RPC.h>

Round::RPC::JSON::BatchRequest::BatchRequest() {
}

Round::RPC::JSON::BatchRequest::~BatchRequest() {
}

void Round::RPC::JSON::BatchRequest::toHTTPPostRequest(uHTTP::HTTPRequest *httpReq) const {
  if (!httpReq)
    return;
  
  httpReq->setMethod(RPC::JSON::HTTP::METHOD);
  httpReq->setURI(RPC::JSON::HTTP::ENDPOINT);
  httpReq->setContentType(RPC::JSON::HTTP::CONTENT_TYPE);
  
  std::string jsonString;
  toJSONString(&jsonString);
  httpReq->setContent(jsonString);
}
