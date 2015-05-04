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

const std::string Round::remove_timer::NAME   = ROUNDCC_SYSTEM_METHOD_REMOVE_TIMER;

Round::remove_timer::remove_timer() : system_method(NAME) {
}

Round::remove_timer::~remove_timer() {
}

bool Round::remove_timer::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  return false;
}
