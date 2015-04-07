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
  setTimestamp(0);
  setLogicalTimestamp(0);
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

bool Round::Registry::setValue(const std::string &value) {
  this->value = value;
  return true;
}

bool Round::Registry::getValue(std::string *value) const {
  if (this->value.length() <= 0)
    return false;
  *value = this->value;
  return  true;
}

bool Round::Registry::setTimestamp(const time_t value) {
  this->ts = value;
  return true;
}

bool Round::Registry::getTimestamp(time_t &value) const {
  if (this->ts <= 0)
    return false;
  value = this->ts;
  return  true;
}

bool Round::Registry::setLogicalTimestamp(const time_t value) {
  this->lts = value;
  return true;
}

bool Round::Registry::getLogicalTimestamp(time_t &value) const {
  if (this->lts <= 0)
    return false;
  value = this->lts;
  return  true;
}

