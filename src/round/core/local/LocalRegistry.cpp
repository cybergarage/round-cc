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
  LocalRegistry::iterator valueIt = find(key);
  if (valueIt != end()) {
    erase(valueIt);
  }

  insert(std::pair<std::string, std::string>(key, value));
  
  return true;
}

bool Round::LocalRegistry::get(const std::string &key, std::string *value) const {
  LocalRegistry::const_iterator valueIt = find(key);
  if (valueIt == end())
    return false;

  *value = valueIt->second;
  
  return true;
}
