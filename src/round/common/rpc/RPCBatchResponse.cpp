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

Round::RPC::JSON::BatchResponse::BatchResponse() {
}

Round::RPC::JSON::BatchResponse::~BatchResponse() {
}

void Round::RPC::JSON::BatchResponse::toHTTPResponse(uHTTP::HTTPResponse *httpRes) const {
  if (!httpRes)
    return;
  
  std::string resContent;
  toJSONString(&resContent);
  httpRes->setContent(resContent);
}
