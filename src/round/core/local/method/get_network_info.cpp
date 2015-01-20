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

const std::string Round::get_network_info::NAME  = "get_network_info";

Round::get_network_info::get_network_info() : system_method(NAME) {
}

Round::get_network_info::~get_network_info() {
}

bool Round::get_network_info::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetNetworkInfoResponse sysRes(nodeRes);
  return sysRes.setClusters(node);
}
