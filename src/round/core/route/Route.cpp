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

#include <round/core/Route.h>

const std::string Round::Route::NODE_DEFALUT = NODE_LOCAL;
const std::string Round::Route::NODE_LOCAL = "local";
const std::string Round::Route::NODE_ALL = "all";

const std::string Round::Route::CLUSTER_DEFALUT = CLUSTER_LOCAL;
const std::string Round::Route::CLUSTER_LOCAL = "local";

const std::string Round::Route::METHOD_DEFALUT = "";
const std::string Round::Route::TYPE_EVENT = "event";
const std::string Round::Route::TYPE_PIPE = "pipe";

Round::Route::Route() {
}

Round::Route::Route(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  setName(name);
  setSource(srcObj);
  setDestination(destObj);  
}

Round::Route::~Route() {
}

bool Round::Route::setName(const std::string &value) {
  this->name = value;
  return true;
}

bool Round::Route::getName(std::string *value) const {
  if (this->name.length() <= 0)
    return false;
  *value = this->name;
  return  true;
}

bool Round::Route::isName(const std::string &value) const {
  return (this->name.compare(value) == 0) ? true : false;
}

bool Round::Route::hasName() const {
  return (0 < this->name.length()) ? true : false;
}

bool Round::Route::isValid() {
  /* Doesn't check name
  if (this->name.length() <= 0)
    return false;
  */
  
  if (!this->srcObjects.isValid())
    return false;
  if (!this->destObjects.isValid())
    return false;

  if (!isValidType())
    return false;
  
  return true;
}

// Source

bool Round::Route::setSource(const std::string &value) {
  return this->srcObjects.parse(value);
}

// Destination

bool Round::Route::setDestination(const std::string &value) {
  return this->destObjects.parse(value);
}

// Type

bool Round::Route::setType(const std::string &value) {
  this->type = value;
  return true;
}

bool Round::Route::isPipe() {
  return (this->type.compare(TYPE_PIPE) == 0);
}

bool Round::Route::isEvent() {
  return (this->type.compare(TYPE_EVENT) == 0);
}

bool Round::Route::isValidType() {
  if (!hasType())
    return true;
  if (isPipe())
    return true;
  if (isEvent())
    return true;
  return false;
}

bool Round::Route::setCondition(const std::string &value) {
  this->cond = value;
  return true;
}

// equals

bool Round::Route::equals(const Route *otherRoute) const {
  if (!otherRoute)
    return false;
  
  /* Doesn't check name
  std::string otherRouteName;
  if (!otherRoute->getName(&otherRouteName))
    return false;
  if (!this->isName(otherRouteName))
    return false;
  */
  
  if (!this->srcObjects.equals(otherRoute->getSourceObjects()))
    return false;
  
  if (!this->destObjects.equals(otherRoute->getDestinationObjects()))
    return false;

  return true;
}
