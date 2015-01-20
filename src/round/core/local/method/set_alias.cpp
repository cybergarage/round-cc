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

const std::string Round::set_alias::NAME = "set_alias";

Round::set_alias::set_alias() : system_method(NAME) {
}

Round::set_alias::~set_alias() {
}

bool Round::set_alias::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
