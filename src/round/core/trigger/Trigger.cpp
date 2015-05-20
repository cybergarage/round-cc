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

Round::Trigger::Trigger(const std::string &name, const std::string &obj, const std::string &defaults) {
  setName(name);
  setObject(obj);
  setDefaults(defaults);
}

bool Round::Trigger::isValid() {
  if (this->name.length() <= 0)
    return false;
  if (this->object.length() <= 0)
    return false;
  return true;
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

bool Round::Trigger::setObject(const std::string &value) {
  this->object = value;
  return true;
}

bool Round::Trigger::getObject(std::string *value) const {
  if (this->object.length() <= 0)
    return false;
  *value = this->object;
  return  true;
}

bool Round::Trigger::setDefaults(const std::string &value) {
  this->defaults = value;
  return true;
}

bool Round::Trigger::getDefaults(std::string *value) const {
  *value = this->defaults;
  return  true;
}

bool Round::Trigger::equals(const Trigger *otherTrigger) const {
  if (!otherTrigger)
    return false;

  std::string name;
  otherTrigger->getName(&name);
  if (this->name.compare(name) != 0)
    return false;
  
  std::string obj;
  otherTrigger->getObject(&obj);
  if (this->object.compare(obj) != 0)
    return false;
  
  std::string defaults;
  otherTrigger->getDefaults(&defaults);
  if (this->defaults.compare(defaults) != 0)
    return false;
  
  return true;
}
