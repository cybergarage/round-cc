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

const std::string Round::get_nodes::NAME = ROUNDCC_SYSTEM_METHOD_GET_NODES;

Round::get_nodes::get_nodes() : system_method(NAME) {
}

Round::get_nodes::~get_nodes() {
}

bool Round::get_nodes::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  return sysRes.setCluster(node);
}
