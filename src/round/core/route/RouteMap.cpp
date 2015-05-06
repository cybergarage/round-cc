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
  for (RouteMap::iterator routeListIt = begin(); routeListIt != end(); routeListIt++) {
    RouteList *routeList = routeListIt->second;
    if (routeList) {
      delete routeList;
    }
  }
  std::map<std::string, RouteList *>::clear();
}

bool Round::RouteMap::addRoute(const Route route) {
  return false;
}
