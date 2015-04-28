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

const std::string Round::get_clusters::NAME  = ROUNDCC_SYSTEM_METHOD_GET_CLUSTERS;

Round::get_clusters::get_clusters() : system_method(NAME) {
}

Round::get_clusters::~get_clusters() {
}

bool Round::get_clusters::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetNetworkInfoResponse sysRes(nodeRes);
  return sysRes.setClusters(node);
}
