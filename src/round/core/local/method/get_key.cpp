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

const std::string Round::get_key::NAME   = "get_key";
const std::string Round::get_key::KEY    = "key";

Round::get_key::get_key() : SystemMethod(NAME) {
}

Round::get_key::~get_key() {
}

bool Round::get_key::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string key;
  if (!nodeReq->get(KEY, &key))
    return false;
  
  std::string value;
  if (!node->getKey(key, &value))
    return false;

  return nodeRes->setResult(value);
}
