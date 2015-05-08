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

bool Round::RouteMap::addRoute(Route *route) {
  if (!route)
    return false;
  
  std::string srcPath;
  const RouteObjects &srcObjs = route->getSourceObjects();
  srcObjs.toString(&srcPath);
  
  RouteList *mapRouteList = getRouteListBySourcePath(srcPath);
  if (!mapRouteList) {
    mapRouteList = new RouteList();
    insert(std::pair<std::string, RouteList *>(srcPath, mapRouteList));
  }
  
  mapRouteList->add(route);
  
  return true;
}

bool Round::RouteMap::setRoute(Route *route) {
  if (!route)
    return false;
  
  return true;
}

Round::RouteList *Round::RouteMap::getRouteListByRoute(Route *route) {
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
  if (routeMapIt == end())
    return NULL;
  return routeMapIt->second;
}
