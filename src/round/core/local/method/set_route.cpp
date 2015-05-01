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

const std::string Round::set_route::NAME        = ROUNDCC_SYSTEM_METHOD_SET_ROUTE;
const std::string Round::set_route::ROUTE_NAME  = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::set_route::ROUTE_SRC   = ROUNDCC_SYSTEM_METHOD_PARAM_SRC;
const std::string Round::set_route::ROUTE_DEST  = ROUNDCC_SYSTEM_METHOD_PARAM_DEST;
const std::string Round::set_route::ROUTE_TYPE  = ROUNDCC_SYSTEM_METHOD_PARAM_TYPE;
const std::string Round::set_route::ROUTE_COND  = ROUNDCC_SYSTEM_METHOD_PARAM_COND;

Round::set_route::set_route() : system_method(NAME) {
}

Round::set_route::~set_route() {
}

bool Round::set_route::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
