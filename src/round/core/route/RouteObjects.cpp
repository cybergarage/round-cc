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

#include <string.h>

const std::string Round::RouteObjects::OBJECT_SEP = ".";
const int Round::RouteObjects::OBJECT_NUM = 3;

const int Round::RouteObjects::TARGET = 0;
const int Round::RouteObjects::NODE = 1;
const int Round::RouteObjects::CLUSTER = 2;

Round::RouteObjects::RouteObjects() {
}

Round::RouteObjects::RouteObjects(const std::string &value) {
  parse(value);
}

Round::RouteObjects::~RouteObjects() {
}

bool Round::RouteObjects::isValid() const {
  if (size() != OBJECT_NUM)
    return false;
  return true;
}

bool Round::RouteObjects::parse(const std::string &value) {
  clear();
  
  if (value.length() <= 0)
    return false;
  
  std::list<std::string> objectList;
  boost::split(objectList, value, boost::is_any_of(OBJECT_SEP));

  size_t objectSize = objectList.size();
  if ((objectSize < 1) || (OBJECT_NUM < objectSize))
    return false;
  
  this->insert(std::pair<int, std::string>(TARGET, Route::METHOD_DEFALUT));
  this->insert(std::pair<int, std::string>(NODE, Route::NODE_DEFALUT));
  this->insert(std::pair<int, std::string>(CLUSTER, Route::CLUSTER_DEFALUT));

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

bool Round::RouteObjects::getObject(int objIdx, std::string *value) const {
  RouteObjects::const_iterator objIt = find(objIdx);
  if (objIt == end())
    return false;
  *value = objIt->second;
  return true;
}

bool Round::RouteObjects::equals(const RouteObjects &otherObj) const {
  if (!isValid() || !otherObj.isValid())
    return false;
  
  for (RouteObjects::const_iterator objIt = begin(); objIt != end(); objIt++) {
    int objIdx = objIt->first;
    std::string objVal = objIt->second;
    RouteObjects::const_iterator otherObjIt = otherObj.find(objIdx);
    if (otherObjIt == otherObj.end())
      return false;
    if (objVal.compare(otherObjIt->second) != 0)
      return false;
  }
  
  return true;
}

bool Round::RouteObjects::isMethod(const std::string &value) const {
  std::string thisValue;
  if (!getTarget(&thisValue))
    return false;
  return (thisValue.compare(value) == 0) ? true : false;
}

bool Round::RouteObjects::isNode(const std::string &value) const {
  std::string thisValue;
  if (!getNode(&thisValue))
    return false;
  return (thisValue.compare(value) == 0) ? true : false;
}

bool Round::RouteObjects::isCluster(const std::string &value) const {
  std::string thisValue;
  if (!getCluster(&thisValue))
    return false;
  return (thisValue.compare(value) == 0) ? true : false;
}

bool Round::RouteObjects::equals(const std::string &otherRoute) const {
  RouteObjects otherRouteObjs(otherRoute);
  return equals(otherRouteObjs);
}

bool Round::RouteObjects::toString(std::string *value) const {
  if (!value)
    return false;
  
  *value = "";
  for (int n=(OBJECT_NUM-1); 0<=n; n--) {
    std::string objStr;
    if (!getObject(n, &objStr))
      continue;
    if (0 < (*value).length()) {
      *value += OBJECT_SEP;
    }
    *value += objStr;
  }
  return true;
}
