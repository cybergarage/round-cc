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

const std::string Round::get_node_config::NAME = "get_node_config";

Round::get_node_config::get_node_config() : system_method(NAME) {
}

Round::get_node_config::~get_node_config() {
}

bool Round::get_node_config::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  Error error;
  JSONDictionary *configDict = new JSONDictionary();
  if (!node->getConfig(configDict, &error)) {
    delete configDict;
    return false;
  }
  return nodeRes->setResult(configDict);
}
