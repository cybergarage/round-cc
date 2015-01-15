/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
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

Round::Route::Route() {
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

bool Round::Route::isValid() {
  if (this->name.length() <= 0)
    return false;
  if (!this->srcObjects.isValid())
    return false;
  if (!this->destObjects.isValid())
    return false;
  return true;
}

bool Round::Route::setSource(const std::string &value) {
  return this->srcObjects.parse(value);
}

bool Round::Route::setDestination(const std::string &value) {
  return this->destObjects.parse(value);
}

bool Round::Route::equals(const Route *otherRoute) const {
  if (!otherRoute)
    return false;
  
  std::string otherRouteName;
  if (!otherRoute->getName(&otherRouteName))
    return false;
  if (!this->isName(otherRouteName))
    return false;
  
  if (!this->srcObjects.equals(otherRoute->getSourceObjects()))
    return false;
  
  if (!this->destObjects.equals(otherRoute->getDestinationObjects()))
    return false;

  return true;
}