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

const std::string Round::remove_route::NAME        = ROUNDCC_SYSTEM_METHOD_REMOVE_ROUTE;
const std::string Round::remove_route::ROUTE_NAME  = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::remove_route::ROUTE_SRC   = ROUNDCC_SYSTEM_METHOD_PARAM_SRC;
const std::string Round::remove_route::ROUTE_DEST  = ROUNDCC_SYSTEM_METHOD_PARAM_DEST;

Round::remove_route::remove_route() : system_method(NAME) {
}

Round::remove_route::~remove_route() {
}

bool Round::remove_route::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
