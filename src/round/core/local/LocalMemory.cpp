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

Round::LocalMemory::LocalMemory() {
}

Round::LocalMemory::~LocalMemory() {
}

bool Round::LocalMemory::setKey(const std::string &key, const std::string &value) {
  LocalMemory::iterator valueIt = find(key);
  if (valueIt != end()) {
    erase(valueIt);
  }

  insert(std::pair<std::string, std::string>(key, value));
  
  return true;
}

bool Round::LocalMemory::getKey(const std::string &key, std::string *value) const {
  LocalMemory::const_iterator valueIt = find(key);
  if (valueIt == end())
    return false;

  *value = valueIt->second;
  
  return true;
}
