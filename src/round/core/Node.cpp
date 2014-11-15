/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>

#include <round/Round.h>
#include <round/core/Node.h>
#include <round/core/NodeGraph.h>

const std::string Round::Node::NAME = ROUNDCC_PRODUCT_NAME;
const std::string Round::Node::VER= ROUNDCC_VERSION;

Round::Node::Node() {
  setWeakFlag(false);
}

Round::Node::~Node() {
}

bool Round::Node::hasName() const {
  std::string nodeName;
  if (!getName(&nodeName))
    return false;
  return (0 < nodeName.length() ? true : false);
}

const char *Round::Node::getHashSeed(std::string *seedString) const {
  std::stringstream seedBuf;
  seedBuf << getRequestAddress() << getRequestPort();
  *seedString = seedBuf.str();

  return seedString->c_str();
}
