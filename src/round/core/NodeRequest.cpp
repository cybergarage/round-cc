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
#include <round/core/Node.h>

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

void Round::NodeRequest::setSourceNodeParameters(const Node *node) {
  clock_t localTs = node->getLocalClock();
  setId(localTs);
  setTimestamp(localTs);
}

bool Round::NodeRequest::setHttpRequest(uHTTP::HTTPRequest *httpReq) {
  close();
  
  this->httpReq = httpReq;

  return true;
}
