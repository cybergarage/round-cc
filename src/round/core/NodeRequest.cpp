/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/NodeMessage.h>

const std::string Round::NodeRequest::SYNC = "sync";

Round::NodeRequest::NodeRequest() {
  init();
}

Round::NodeRequest::NodeRequest(const std::string &method) {
  init();
  setMethod(method);
}

void Round::NodeRequest::init() {
  this->httpReq = NULL;
}

Round::NodeRequest::~NodeRequest() {
  close();
}

bool Round::NodeRequest::close() {
  if (!this->httpReq)
    return false;
  
  delete this->httpReq;
  this->httpReq = NULL;

  return true;
}

bool Round::NodeRequest::setHttpRequest(uHTTP::HTTPRequest *httpReq) {
  close();
  
  this->httpReq = httpReq;

  return true;
}
