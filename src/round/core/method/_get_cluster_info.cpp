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

const std::string Round::_get_cluster_info::NAME = "_get_cluster_info";

Round::_get_cluster_info::_get_cluster_info() : Method(NAME) {
}

Round::_get_cluster_info::~_get_cluster_info() {
}

bool Round::_get_cluster_info::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) const {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  return sysRes.setCluster(node);
}
