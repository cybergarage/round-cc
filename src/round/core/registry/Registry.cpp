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

Round::Registry::Registry() {
}

Round::Registry::~Registry() {
}

bool Round::Registry::setKey(const std::string &value) {
  this->key = value;
  return true;
}

bool Round::Registry::getKey(std::string *value) const {
  if (this->key.length() <= 0)
    return false;
  *value = this->key;
  return  true;
}
