/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Message.h>

Round::Message::Message() {
  init();
}

Round::Message::~Message() {
  close();
}

void Round::Message::init() {
  this->httpReq = NULL;
}

bool Round::Message::setHttpRequest(uHTTP::HTTPRequest *httpReq) {
  close();
  this->httpReq = httpReq;
  return true;
}

bool Round::Message::close() {
  if (!this->httpReq)
    return false;
  
  delete this->httpReq;
  this->httpReq = NULL;
  
  return true;
}
