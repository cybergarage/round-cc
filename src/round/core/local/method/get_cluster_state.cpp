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

const std::string Round::get_cluster_state::NAME = ROUNDCC_SCRIPT_GET_CLUSTER_STATE;

Round::get_cluster_state::get_cluster_state() : system_method(NAME) {
}

Round::get_cluster_state::~get_cluster_state() {
}

bool Round::get_cluster_state::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  return sysRes.setCluster(node);
}
