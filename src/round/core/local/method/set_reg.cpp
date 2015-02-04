/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/local/method/SystemMethod.h>

const std::string Round::set_reg::NAME   = "set_reg";
const std::string Round::set_reg::KEY    = "key";
const std::string Round::set_reg::VALUE  = "value";

Round::set_reg::set_reg() : system_method(NAME) {
}

Round::set_reg::~set_reg() {
}

bool Round::set_reg::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string key;
  if (!nodeReq->get(KEY, &key))
    return false;
  
  std::string value;
  if (!nodeReq->get(VALUE, &value))
    return false;
  
  return node->setKey(key, value);
}
