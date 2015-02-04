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

const std::string Round::get_reg::NAME   = "get_reg";
const std::string Round::get_reg::KEY    = "key";

Round::get_reg::get_reg() : system_method(NAME) {
}

Round::get_reg::~get_reg() {
}

bool Round::get_reg::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string key;
  if (!nodeReq->get(KEY, &key))
    return false;
  
  std::string value;
  if (!node->getKey(key, &value))
    return false;

  return nodeRes->setResult(value);
}
