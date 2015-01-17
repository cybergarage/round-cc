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

Round::RouteList::RouteList() {
}

Round::RouteList::~RouteList() {
}

bool Round::RouteList::addRoute(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  if (getRouteByName(name))
    return false;
  
  Route *route = new Route();
  if (!route)
    return false;
  
  route->setName(name);
  route->setSource(srcObj);
  route->setDestination(destObj);
  
  if (!route->isValid()) {
    delete route;
    return false;
  }

  lock();
  
  bool isSuccess = add(route);

  unlock();

  return isSuccess;
}

bool Round::RouteList::setRoute(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  Route *route = getRouteByName(name);
  if (route) {
    lock();
    erase(route);
    unlock();
  }
  
  return addRoute(name, srcObj, destObj);
}

Round::Route *Round::RouteList::getRouteByName(const std::string &name) const {

  lock();
  
  Route *foundRuote = NULL;
  
  for (RouteList::const_iterator routeIt = begin(); routeIt != end(); routeIt++) {
    Route *route = *routeIt;
    if (route->isName(name)) {
      foundRuote = route;
      break;
    }
  }

  unlock();

  return foundRuote;
}

Round::Route *Round::RouteList::getRouteBySouceObject(const std::string &srcObject) const {
  lock();
  
  Route *foundRuote = NULL;
  
  for (RouteList::const_iterator routeIt = begin(); routeIt != end(); routeIt++) {
    Route *route = *routeIt;
    RouteObjects srcObjs = route->getSourceObjects();
    if (srcObjs.equals(srcObject)) {
      foundRuote = route;
      break;
    }
  }
  
  unlock();
  
  return foundRuote;
  
}

Round::Route *Round::RouteList::getRouteBySouceMethod(const std::string &srcMethod) const {
  lock();
  
  Route *foundRuote = NULL;
  
  for (RouteList::const_iterator routeIt = begin(); routeIt != end(); routeIt++) {
    Route *route = *routeIt;
    RouteObjects srcObjs = route->getSourceObjects();
    if (srcObjs.isMethod(srcMethod)) {
      foundRuote = route;
      break;
    }
  }
  
  unlock();
  
  return foundRuote;
  
}
