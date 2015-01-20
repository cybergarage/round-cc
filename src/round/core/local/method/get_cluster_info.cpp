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

const std::string Round::get_cluster_info::NAME = "get_cluster_info";

Round::get_cluster_info::get_cluster_info() : system_method(NAME) {
}

Round::get_cluster_info::~get_cluster_info() {
}

bool Round::get_cluster_info::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  return sysRes.setCluster(node);
}
