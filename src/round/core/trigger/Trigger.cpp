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

#include <round/core/Trigger.h>

Round::Trigger::Trigger() {
}

Round::Trigger::~Trigger() {
}

bool Round::Trigger::setName(const std::string &value) {
  this->name = value;
  return true;
}

bool Round::Trigger::getName(std::string *value) const {
  if (this->name.length() <= 0)
    return false;
  *value = this->name;
  return  true;
}

bool Round::Trigger::isName(const std::string &value) const {
  return (this->name.compare(value) == 0) ? true : false;
}
