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

bool Round::Registry::equals(const Registry &otherReg) const {
  return equals(&otherReg);
}

bool Round::Registry::equals(const Registry *otherReg) const {
  if (!otherReg)
    return false;
  
  std::string otherKey;
  if (!otherReg->getKey(&otherKey))
    return false;
  if (this->key.compare(otherKey) != 0)
    return false;

  std::string otherVal;
  if (!otherReg->getValue(&otherVal))
    return false;
  if (this->value.compare(otherVal) != 0)
    return false;
  
  return true;
}

bool Round::Registry::equalsWithTimestamp(const Registry &otherReg) const {
  return equalsWithTimestamp(&otherReg);
}

bool Round::Registry::equalsWithTimestamp(const Registry *otherReg) const {
  if (!equals(otherReg))
    return false;
  if (!otherReg)
    return false;
 
  time_t otherTs;
  
  if (!otherReg->getTimestamp(otherTs))
    return false;
  if (this->ts != otherTs)
    return false;
  
  if (!otherReg->getLogicalTimestamp(otherTs))
    return false;
  if (this->lts != otherTs)
    return false;
  
  return true;
}
