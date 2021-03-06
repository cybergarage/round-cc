/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/local/method/SystemMethod.h>

const std::string Round::set_route::NAME        = ROUNDCC_SYSTEM_METHOD_SET_ROUTE;
const std::string Round::set_route::ROUTE_NAME  = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::set_route::ROUTE_SRC   = ROUNDCC_SYSTEM_METHOD_PARAM_SRC;
const std::string Round::set_route::ROUTE_DEST  = ROUNDCC_SYSTEM_METHOD_PARAM_DEST;
const std::string Round::set_route::ROUTE_TYPE  = ROUNDCC_SYSTEM_METHOD_PARAM_TYPE;
const std::string Round::set_route::ROUTE_COND  = ROUNDCC_SYSTEM_METHOD_PARAM_COND;

Round::set_route::set_route() : system_method(NAME) {
}

Round::set_route::~set_route() {
}

bool Round::set_route::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string params;
  if (!nodeReq->getParams(&params))
    return false;
  
  JSONParser jsonParser;
  Error error;
  if (!jsonParser.parse(params, &error))
    return false;
  
  JSONDictionary *paramDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  if (!paramDict)
    return false;
  
  // Essential Parameters
  
  std::string src, dest;
  
  if (!paramDict->get(ROUTE_SRC, &src))
    return false;
  
  if (!paramDict->get(ROUTE_DEST, &dest))
    return false;

  if ((src.length() <= 0) || (dest.length() <= 0))
    return false;
  
  // Optional Parameters
  
  std::string name, type, cond;

  paramDict->get(ROUTE_NAME, &name);
  paramDict->get(ROUTE_TYPE, &type);
  paramDict->get(ROUTE_COND, &cond);
  
  // Set route
  
  Route *route = new Route();
  if (!route)
    return false;
  
  route->setName(name);
  route->setSource(src);
  route->setDestination(dest);
  route->setType(type);
  route->setCondition(cond);
  
  if (!node->setRoute(route)) {
    delete route;
    return false;
  }
  
  return true;
}
