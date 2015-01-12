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

const std::string Round::RouteObjects::OBJECT_SEP = ".";
const int Round::RouteObjects::OBJECT_NUM = 3;

const int Round::RouteObjects::METHOD = 0;
const int Round::RouteObjects::NODE = 1;
const int Round::RouteObjects::CLUSTER = 2;

Round::RouteObjects::RouteObjects() {
}

Round::RouteObjects::RouteObjects(const std::string &value) {
  parse(value);
}

Round::RouteObjects::~RouteObjects() {
}

bool Round::RouteObjects::isValid() {
  if (size() != OBJECT_NUM)
    return false;
  return true;
}

bool Round::RouteObjects::parse(const std::string &value) {
  clear();
  
  std::list<std::string> objectList;
  boost::split(objectList, value, boost::is_any_of(OBJECT_SEP));

  size_t objectSize = objectList.size();
  if ((objectSize < 1) || (3 < objectSize))
    return false;
  
  this->insert(std::pair<int, std::string>(Route::METHOD, Route::METHOD_DEFALUT));
  this->insert(std::pair<int, std::string>(Route::NODE, Route::NODE_DEFALUT));
  this->insert(std::pair<int, std::string>(Route::CLUSTER, Route::CLUSTER_DEFALUT));

  int objectIdx = 0;
  BOOST_REVERSE_FOREACH(std::string object, objectList) {
    RouteObjects::iterator objIt = find(objectIdx);
    if (objIt != RouteObjects::end()) {
      erase(objIt);
    }
    this->insert(std::pair<int, std::string>(objectIdx, object));
    objectIdx++;
  }
  
  return true;
}

bool Round::RouteObjects::getObject(int objectIdx, std::string *value) {
  RouteObjects::iterator objectIt = find(objectIdx);
  if (objectIt == end())
    return false;
  *value = objectIt->second;
  return true;
}
