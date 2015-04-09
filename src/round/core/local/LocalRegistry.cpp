/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>

Round::LocalRegistry::LocalRegistry() {
  setNode(NULL);
}

Round::LocalRegistry::~LocalRegistry() {
  setNode(NULL);
}

void Round::LocalRegistry::setNode(LocalNode *node) {
  this->node = node;
}

bool Round::LocalRegistry::set(const std::string &key, const std::string &value) {
  Registry reg;
  
  reg.setKey(key);
  reg.setValue(value);
  
  time_t ts;
  reg.setTimestamp(time(&ts));
  
  if (this->node) {
    Clock nodeClode;
    reg.setLogicalTimestamp(this->node->getLocalClock());
  }

  return RegistryMap::set(reg);
}
