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

const std::string Round::NodeRequest::KEY_METHOD = "_method";

Round::NodeRequest::NodeRequest() {
}

Round::NodeRequest::NodeRequest(const std::string &method) {
  set(KEY_METHOD, method);
}

Round::NodeRequest::~NodeRequest() {
}

bool Round::NodeRequest::hasMethod() const {
  return hasKey(KEY_METHOD);
}

bool Round::NodeRequest::isMethod(const std::string &method) const {
  std::string reqMethod;
  if (!get(KEY_METHOD, &reqMethod))
    return false;
  return (method.compare(reqMethod) == 0) ? true : false;
}

bool Round::NodeRequest::isValid() {
  return false;
}
