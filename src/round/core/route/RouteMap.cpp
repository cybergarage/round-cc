/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Route.h>

Round::RouteMap::RouteMap() {
}

Round::RouteMap::~RouteMap() {
  clear();
}

void Round::RouteMap::clear() {
  for (RouteMap::iterator routeMapIt = begin(); routeMapIt != end(); routeMapIt++) {
    RouteList *routeList = routeMapIt->second;
    if (routeList) {
      delete routeList;
    }
  }
  std::map<std::string, RouteList *>::clear();
}

size_t Round::RouteMap::count() {
  size_t totalCount = 0;
  
  for (RouteMap::iterator routeMapIt = begin(); routeMapIt != end(); routeMapIt++) {
    RouteList *routeList = routeMapIt->second;
    totalCount += routeList->size();
  }
  
  return totalCount;
}

bool Round::RouteMap::addRoute(Route *route) {
  if (!route)
    return false;
  
  RouteList *mapRouteList = getRouteListByRoute(route);
  if (!mapRouteList)
    return false;
  
  return mapRouteList->addRoute(route);
}

bool Round::RouteMap::setRoute(Route *route) {
  if (!route)
    return false;
  
  RouteList *mapRouteList = getRouteListByRoute(route);
  if (!mapRouteList)
    return false;
  
  return mapRouteList->setRoute(route);
}

bool Round::RouteMap::addRoute(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  Route *route = new Route(name, srcObj, destObj);
  if (!route)
    return false;
  
  bool isSuccess = addRoute(route);
  if (!isSuccess) {
    delete route;
  }
  
  return isSuccess;
}

bool Round::RouteMap::setRoute(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  Route *route = new Route(name, srcObj, destObj);
  if (!route)
    return false;
  
  bool isSuccess = setRoute(route);
  if (!isSuccess) {
    delete route;
  }
  
  return isSuccess;
}

Round::RouteList *Round::RouteMap::findRouteListByRoute(const Route *route) const {
  if (!route)
    return NULL;
  
  std::string srcPath;
  const RouteObjects &srcObjs = route->getSourceObjects();
  if (!srcObjs.toString(&srcPath))
    return NULL;
  
  return findRouteListBySourcePath(srcPath);
}

Round::RouteList *Round::RouteMap::findRouteListBySourcePath(const std::string &srcPath) const {
  RouteMap::const_iterator routeMapIt = find(srcPath);
  if (routeMapIt != end())
    return routeMapIt->second;

  return NULL;
}

Round::RouteList *Round::RouteMap::getRouteListByRoute(const Route *route) {
  if (!route)
    return NULL;
  
  std::string srcPath;
  const RouteObjects &srcObjs = route->getSourceObjects();
  if (!srcObjs.toString(&srcPath))
    return NULL;
  
  return getRouteListBySourcePath(srcPath);
}

Round::RouteList *Round::RouteMap::getRouteListBySourcePath(const std::string &srcPath) {
  RouteMap::iterator routeMapIt = find(srcPath);
  if (routeMapIt != end())
    return routeMapIt->second;

  RouteList *mapRouteList = new RouteList();
  insert(std::pair<std::string, RouteList *>(srcPath, mapRouteList));
  return mapRouteList;
}

Round::Route *Round::RouteMap::findSameRoute(const Route *otherRoute) const {
  RouteList *routeList = findRouteListByRoute(otherRoute);
  if (!routeList)
    return NULL;
  return routeList->findSameRoute(otherRoute);
}

Round::Route *Round::RouteMap::findRouteByName(const std::string &name) const {
  for (RouteMap::const_iterator routeMapIt = begin(); routeMapIt != end(); routeMapIt++) {
    RouteList *routeList = routeMapIt->second;
    Route *route = routeList->findRouteByName(name);
    if (route)
      return route;
  }
  return NULL;
}
