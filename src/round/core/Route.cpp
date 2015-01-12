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

#include <string.h>

const std::string Round::Route::OBJECT_SEP = ".";
const int Round::Route::OBJECT_NUM = 3;

const int Round::Route::METHOD = 0;
const int Round::Route::NODE = 1;
const int Round::Route::CLUSTER = 2;

const std::string Round::Route::NODE_DEFALUT = NODE_LOCAL;
const std::string Round::Route::NODE_LOCAL = "local";
const std::string Round::Route::NODE_ALL = "all";

const std::string Round::Route::CLUSTER_DEFALUT = CLUSTER_LOCAL;
const std::string Round::Route::CLUSTER_LOCAL = "local";

Round::Route::Route() {
}

Round::Route::~Route() {
}

bool Round::Route::isValid() {
  if (this->srcObjects.size() != OBJECT_NUM)
    return false;
  if (this->destObjects.size() != OBJECT_NUM)
    return false;
  return true;
}

bool Round::Route::parseObject(const std::string &value, RouteObjects &objectMap) {
  std::list<std::string> objectList;
  boost::split(objectList, value, boost::is_any_of(OBJECT_SEP));

  size_t objectSize = objectList.size();
  if ((objectSize < 1) || (3 < objectSize))
    return false;
  
  objectMap[METHOD] = "";
  objectMap[NODE] = NODE_DEFALUT;
  objectMap[CLUSTER] = CLUSTER_DEFALUT;

  int objectIdx = 0;
  BOOST_REVERSE_FOREACH(std::string object, objectList) {
    objectMap[objectIdx] = object;
    objectIdx++;
  }
  
  return true;
}

bool Round::Route::setSource(const std::string &value) {
  return parseObject(value, this->srcObjects);
}

bool Round::Route::setDestination(const std::string &value) {
  return parseObject(value, this->destObjects);
}

bool Round::Route::getObject(RouteObjects &objects, int objectIdx, std::string *value) {
  RouteObjects::iterator objectIt = objects.find(objectIdx);
  if (objectIt == objects.end())
    return false;
  *value = objectIt->second;
  return true;
}
