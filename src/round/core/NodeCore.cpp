/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <algorithm>
#include <sstream>

#include <round/Round.h>
#include <round/core/NodeCore.h>

Round::NodeCore::NodeCore() {
}

Round::NodeCore::~NodeCore() {
}

clock_t Round::NodeCore::getLocalClock() const {
  return this->clock.getValue();
}

clock_t Round::NodeCore::incrementLocalClock() {
  return this->clock.increment();
}

clock_t Round::NodeCore::setRemoteClock(clock_t value) {
  this->clock.setValue(std::max(value, this->clock.getValue()));
  return this->clock.increment();
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
