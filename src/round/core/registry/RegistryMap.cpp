/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/algorithm/string.hpp> 
#include <boost/foreach.hpp>
#include <list>

#include <round/core/Registry.h>

Round::RegistryMap::RegistryMap() {
}

Round::RegistryMap::~RegistryMap() {
}

bool Round::RegistryMap::set(const Registry reg) {
  std::string key;
  if (!reg.getKey(&key))
    return false;
  RegistryMap::iterator valueIt = find(key);
  if (valueIt != end()) {
    valueIt->second = reg;
    return true;
  }

  insert(std::pair<std::string, Registry>(key, reg));
  
  return true;
}

bool Round::RegistryMap::get(const std::string &key, Registry *reg) const {
  RegistryMap::const_iterator valueIt = find(key);
  if (valueIt == end())
    return false;
  
  *reg = valueIt->second;
  
  return true;
}
