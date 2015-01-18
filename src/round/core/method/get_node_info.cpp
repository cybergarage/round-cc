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

#include <round/core/method/SystemMethod.h>

const std::string Round::get_node_info::NAME = "get_node_info";

Round::get_node_info::get_node_info() : SystemMethod(NAME) {
}

Round::get_node_info::~get_node_info() {
}

bool Round::get_node_info::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetNodeInfoResponse sysRes(nodeRes);
  return sysRes.setNode(node);
}
