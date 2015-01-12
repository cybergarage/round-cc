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

#include <round/common/Vector.h>

namespace Round {

typedef std::map<int, std::string> RouteObjects;
  
class Route {

private:
  
  static const std::string OBJECT_SEP;
  static const int OBJECT_NUM;

public:
  
  static const int METHOD;
  static const int NODE;
  static const int CLUSTER;
  
  static const std::string NODE_DEFALUT;
  static const std::string NODE_LOCAL;
  static const std::string NODE_ALL;
  
  static const std::string CLUSTER_DEFALUT;
  static const std::string CLUSTER_LOCAL;
  
public:
  Route();
  virtual ~Route();

  bool isValid();
  
  bool setName(const std::string &value);
  bool getName(std::string *value);
  
  bool setSource(const std::string &value);
  bool setDestination(const std::string &value);
  
  bool getSourceMethod(std::string *value) {
    return getSourceObject(METHOD, value);
  }
  bool getSourceNode(std::string *value) {
    return getSourceObject(NODE, value);
  }

  bool getSourceCluster(std::string *value) {
    return getSourceObject(CLUSTER, value);
  }

  bool getDestinationMethod(std::string *value) {
    return getDestinationObject(METHOD, value);
  }
  bool getDestinationNode(std::string *value) {
    return getDestinationObject(NODE, value);
  }
  
  bool getDestinationCluster(std::string *value) {
    return getDestinationObject(CLUSTER, value);
  }
  
private:
  
  bool parseObject(const std::string &value, RouteObjects &objects);
  
  bool getObject(RouteObjects &objects, int objIdx, std::string *value);
  
  bool getSourceObject(int objIdx, std::string *value) {
    return getObject(this->srcObjects, objIdx, value);
  }
  
  bool getDestinationObject(int objIdx, std::string *value) {
    return getObject(this->destObjects, objIdx, value);
  }
  
private:
  
  std::string  name;
  RouteObjects srcObjects;
  RouteObjects destObjects;
};

class RouteList : public Vector<Route> {
    
 public:
  
  RouteList();
  ~RouteList();
  
  bool addRoute(const std::string &name, const std::string &srcObject, const std::string *destObject);

  Route *getRouteByName(const std::string &name);
  Route *getRouteBySouceObject(const std::string &srcObject);
};

class RouteEngine : public RouteList {
    
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
