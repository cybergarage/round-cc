/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>

#include <round/Round.h>
#include <round/core/NodeCore.h>

Round::NodeCore::NodeCore() {
}

Round::NodeCore::~NodeCore() {
}

const char *Round::NodeCore::getHashSeed(std::string *seedString) const {
  std::stringstream seedBuf;
  seedBuf << getRequestAddress() << getRequestPort();
  *seedString = seedBuf.str();
  return seedString->c_str();
}
