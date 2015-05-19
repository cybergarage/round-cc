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

const std::string Round::add_node::NAME = ROUNDCC_SYSTEM_METHOD_ADD_NODE;

Round::add_node::add_node() : system_method(NAME) {
}

Round::add_node::~add_node() {
}

bool Round::add_node::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return (system(ROUNDCC_SYSTEM_METHOD_ADD_NODE_CMD) == 0) ? true : false;
}
