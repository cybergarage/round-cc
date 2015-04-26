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

const std::string Round::get_node_state::NAME = ROUNDCC_SCRIPT_GET_NODE_STATE;

Round::get_node_state::get_node_state() : system_method(NAME) {
}

Round::get_node_state::~get_node_state() {
}

bool Round::get_node_state::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetNodeInfoResponse sysRes(nodeRes);
  return sysRes.setNode(node);
}
