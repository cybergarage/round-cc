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

const std::string Round::SystemMethod::ECHO = "_echo";

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
