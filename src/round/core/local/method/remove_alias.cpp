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

const std::string Round::remove_alias::NAME = ROUNDCC_SYSTEM_METHOD_REMOVE_ALIAS;

Round::remove_alias::remove_alias() : system_method(NAME) {
}

Round::remove_alias::~remove_alias() {
}

bool Round::remove_alias::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
