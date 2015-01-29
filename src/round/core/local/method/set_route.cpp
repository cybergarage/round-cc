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

const std::string Round::set_route::NAME   = "set_route";
const std::string Round::set_route::ROUTE_NAME          = "name";
const std::string Round::set_route::ROUTE_SRC           = "src";
const std::string Round::set_route::ROUTE_DEST          = "dest";
const std::string Round::set_route::ROUTE_TYPE          = "type";
const std::string Round::set_route::ROUTE_COND          = "cond";

Round::set_route::set_route() : system_method(NAME) {
}

Round::set_route::~set_route() {
}

bool Round::set_route::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
