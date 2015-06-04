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

Round::Alias::Alias(const std::string &name, const std::string &obj, const std::string &defaults) {
  setName(name);
  setObject(obj);
  setDefaults(defaults);
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

bool Round::Alias::setDefaults(const std::string &value) {
  this->defaults = value;
  return true;
}

bool Round::Alias::getDefaults(std::string *value) const {
  *value = this->defaults;
  return  true;
}

bool Round::Alias::equals(const Alias *otherAlias) const {
  if (!otherAlias)
    return false;

  std::string name;
  otherAlias->getName(&name);
  if (this->name.compare(name) != 0)
    return false;
  
  std::string obj;
  otherAlias->getObject(&obj);
  if (this->object.compare(obj) != 0)
    return false;
  
  std::string defaults;
  otherAlias->getDefaults(&defaults);
  if (this->defaults.compare(defaults) != 0)
    return false;
  
  return true;
}
