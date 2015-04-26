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

const std::string Round::get_network_state::NAME  = ROUNDCC_SCRIPT_GET_NETWORK_STATE;

Round::get_network_state::get_network_state() : system_method(NAME) {
}

Round::get_network_state::~get_network_state() {
}

bool Round::get_network_state::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  SystemGetNetworkInfoResponse sysRes(nodeRes);
  return sysRes.setClusters(node);
}
