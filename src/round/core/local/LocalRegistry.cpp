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
}

Round::LocalRegistry::~LocalRegistry() {
}

bool Round::LocalRegistry::set(const std::string &key, const std::string &value) {
  Registry reg;
  reg.setKey(key);
  reg.setValue(value);
  return set(reg);
}
