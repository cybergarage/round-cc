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
  Route *route = new Route(name, srcObj, destObj);
  if (!route)
    return false;

  bool isSuccess = addRoute(route);
  if (!isSuccess) {
    delete route;
  }
  
  return isSuccess;
}

bool Round::RouteList::setRoute(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  Route *route = new Route(name, srcObj, destObj);
  if (!route)
    return false;
  
  bool isSuccess = setRoute(route);
  if (!isSuccess) {
    delete route;
  }
  
  return isSuccess;
}

bool Round::RouteList::addRoute(Route *route) {
  if (!route->isValid())
    return false;
  
  if (findSameRoute(route))
    return false;

  std::string routeName;
  if (route->getName(&routeName)) {
    if (findRouteByName(routeName))
      return false;
  }

  lock();
  
  bool isSuccess = add(route);
  
  unlock();
  
  return isSuccess;
}

bool Round::RouteList::setRoute(Route *route) {
  Route *sameRoute = findSameRoute(route);
  if (!sameRoute) {
    std::string routeName;
    if (route->getName(&routeName)) {
      sameRoute = findRouteByName(routeName);
    }
  }
  
  if (sameRoute) {
    lock();
    remove(sameRoute);
    unlock();
  }
  
  return addRoute(route);
}

Round::Route *Round::RouteList::findSameRoute(const Route *otherRoute) const {
  lock();
  
  Route *foundRuote = NULL;
  
  for (RouteList::const_iterator routeIt = begin(); routeIt != end(); routeIt++) {
    Route *route = *routeIt;
    if (route->equals(otherRoute)) {
      foundRuote = route;
      break;
    }
  }
  
  unlock();
  
  return foundRuote;
}

Round::Route *Round::RouteList::findRouteByName(const std::string &name) const {

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

Round::Route *Round::RouteList::findRouteBySouceObject(const std::string &srcObject) const {
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

Round::Route *Round::RouteList::findRouteBySouceMethod(const std::string &srcMethod) const {
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

bool Round::RouteList::removeSameRoute(const Route *otherRoute) {
  Route *route = findSameRoute(otherRoute);
  if (!route)
    return false;
  return remove(route);
}

bool Round::RouteList::removeRouteByName(const std::string &name) {
  Route *route = findRouteByName(name);
  if (!route)
    return false;
  return remove(route);
}
