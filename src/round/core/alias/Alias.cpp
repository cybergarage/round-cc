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

#include <round/core/Alias.h>

Round::Alias::Alias() {
}

Round::Alias::~Alias() {
}

bool Round::Alias::isValid() {
  if (this->name.length() <= 0)
    return false;
  if (this->object.length() <= 0)
    return false;
  return true;
}

bool Round::Alias::setName(const std::string &value) {
  this->name = value;
  return true;
}

bool Round::Alias::getName(std::string *value) const {
  if (this->name.length() <= 0)
    return false;
  *value = this->name;
  return  true;
}

bool Round::Alias::isName(const std::string &value) const {
  return (this->name.compare(value) == 0) ? true : false;
}

bool Round::Alias::setObject(const std::string &value) {
  this->object = value;
  return true;
}

bool Round::Alias::getObject(std::string *value) const {
  if (this->object.length() <= 0)
    return false;
  *value = this->object;
  return  true;
}
