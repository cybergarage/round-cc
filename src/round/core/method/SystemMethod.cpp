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

const std::string Round::SystemMethod::PREFIX      = "_";
const std::string Round::SystemMethod::ECHO        = "_echo";
const std::string Round::SystemMethod::SET_METHOD  = "_set_method";

Round::SystemMethod::SystemMethod(const std::string &name) : Method(name) {
}

Round::SystemMethod::~SystemMethod() {
}
  
bool Round::SystemMethod::exec(const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  const LocalNode *constLocalNode = dynamic_cast<const LocalNode *>(node);
  if (!constLocalNode)
    return false;
  LocalNode *localNode = const_cast<LocalNode *>(constLocalNode);
  if (!localNode)
    return false;
  return exec(localNode, nodeReq, nodeRes);
}
