/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/RPC.h>

Round::RPC::JSON::Request::Request() {
  set(JSON_RPC, VERSION);
}

Round::RPC::JSON::Request::~Request() {
}

bool Round::RPC::JSON::Request::isValid() {
  if (!hasKey(JSON_RPC))
    return false;

  if (!hasKey(METHOD))
    return false;

  int value;
  if (get(METHOD, &value))
    return false;

  return true;
}

bool Round::RPC::JSON::Request::isNotify() {
  if (!isValid())
    return false;
  return !hasKey(ID);
}

bool Round::RPC::JSON::Request::isMethod(const std::string &method) const {
  std::string reqMethod;
  if (!get(METHOD, &reqMethod))
    return false;
  return (method.compare(reqMethod) == 0) ? true : false;
}

void Round::RPC::JSON::Request::toHTTPRequest(uHTTP::HTTPRequest *httpReq) const {
  if (!httpReq)
    return;
  
  httpReq->setMethod(RPC::HTTP::METHOD);
  httpReq->setURI(RPC::HTTP::ENDPOINT);
  httpReq->setContentType(RPC::HTTP::CONTENT_TYPE);
  
  std::string jsonString;
  toJSONString(&jsonString);
  httpReq->setContent(jsonString);
}
