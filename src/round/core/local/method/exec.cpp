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
#include <stdlib.h>

#include <round/core/local/method/SystemMethod.h>

const std::string Round::execp::NAME = "exec";
const std::string Round::execp::CMD  = "cmd";
const std::string Round::execp::ARGS = "args";

Round::execp::execp() : system_method(NAME) {
}

Round::execp::~execp() {
}

bool Round::execp::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string cmd;
  if (!nodeReq->getParams(&cmd))
    return false;

  if (0 <= system(cmd.c_str()))
    return true;
  
  return false;
}
