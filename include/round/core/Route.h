/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_ROUTE_H_
#define _ROUNDCC_ROUTE_H_

#include <string>
#include <map>

#include <round/common/types.h>
#include <round/common/platform.h>
#include <round/common/Vector.h>
#include <round/common/Error.h>
#include <round/common/RPC.h>
#include <round/common/Mutex.h>

namespace Round {

class Route {

public:
  Route();
  virtual ~Route();
};

class RouteList : public Vector<Route> {
    
 public:
    
  RouteList() {
  }
};

class RouteEngine {
    
public:
    
  RouteEngine();
  virtual ~RouteEngine();
};

class RouteManager {
    
 public:
  
  RouteManager();
  virtual ~RouteManager();
};

}

#endif
