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

clock_t Round::NodeCore::getClock() const {
  return this->clock.getValue();
}

const char *Round::NodeCore::getHashSeed(std::string *seedString) const {
  Error err;
  
  std::string nodeIp;
  getRequestAddress(&nodeIp, &err);

  int nodePort;
  getRequestPort(&nodePort, &err);
  
  std::stringstream seedBuf;
  seedBuf << nodeIp << nodePort;
  
  *seedString = seedBuf.str();
  return seedString->c_str();
}
