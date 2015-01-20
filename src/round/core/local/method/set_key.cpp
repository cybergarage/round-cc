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

const std::string Round::set_key::NAME   = "set_key";
const std::string Round::set_key::KEY    = "key";
const std::string Round::set_key::VALUE  = "value";

Round::set_key::set_key() : system_method(NAME) {
}

Round::set_key::~set_key() {
}

bool Round::set_key::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string key;
  if (!nodeReq->get(KEY, &key))
    return false;
  
  std::string value;
  if (!nodeReq->get(VALUE, &value))
    return false;
  
  return node->setKey(key, value);
}
