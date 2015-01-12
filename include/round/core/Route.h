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

class RouteObjects :public std::map<int, std::string> {

private:
  
  static const std::string OBJECT_SEP;
  static const int OBJECT_NUM;

public:
  
  static const int METHOD;
  static const int NODE;
  static const int CLUSTER;
  
public:
  RouteObjects();
  RouteObjects(const std::string &value);
  ~RouteObjects();
  
  bool isValid() const;
  bool parse(const std::string &value);

  bool getObject(int objIdx, std::string *value) const;

  bool getMethod(std::string *value) const {
    return getObject(METHOD, value);
  }
  
  bool getNode(std::string *value) const {
    return getObject(NODE, value);
  }
  
  bool getCluster(std::string *value) const {
    return getObject(CLUSTER, value);
  }

  bool isMethod(const std::string &value) const;
  bool isNode(const std::string &value) const;
  bool isCluster(const std::string &value) const;
  
  bool equals(const RouteObjects &otherObj) const;
  bool equals(const std::string &otherRoute) const;
};
  
class Route {

public:
  
  static const std::string NODE_DEFALUT;
  static const std::string NODE_LOCAL;
  static const std::string NODE_ALL;
  
  static const std::string CLUSTER_DEFALUT;
  static const std::string CLUSTER_LOCAL;
  
  static const std::string METHOD_DEFALUT;

public:
  Route();
  virtual ~Route();

  bool isValid();
  
  bool setName(const std::string &value);
  bool getName(std::string *value) const;
  bool isName(const std::string &value) const;
  
  bool setSource(const std::string &value);
  bool setDestination(const std::string &value);
  
  const RouteObjects &getSourceObjects() const {
    return this->srcObjects;
  }
  
  const RouteObjects &getDestinationObjects() const {
    return this->destObjects;
  }
  
  bool isSource(const std::string &value) const {
    return this->srcObjects.equals(value);
  }
  
  bool isSourceMethod(const std::string &value) const {
    return this->srcObjects.isMethod(value);
  }
  
  bool getSourceMethod(std::string *value) const {
    return this->srcObjects.getMethod(value);
  }
  
  bool getSourceNode(std::string *value) const {
    return this->srcObjects.getNode(value);
  }

  bool getSourceCluster(std::string *value) const {
    return this->srcObjects.getCluster(value);
  }

  bool isDestination(const std::string &value) const {
    return this->destObjects.equals(value);
  }
  
  bool getDestinationMethod(std::string *value) const {
    return this->destObjects.getMethod(value);
  }
  
  bool getDestinationNode(std::string *value) const {
    return this->destObjects.getNode(value);
  }
  
  bool getDestinationCluster(std::string *value) const {
    return this->destObjects.getCluster(value);
  }
  
  bool equals(const Route *otherRoute) const;
  
private:
  
  std::string  name;
  RouteObjects srcObjects;
  RouteObjects destObjects;
};

class RouteList : public Vector<Route> {
    
 public:
  
  RouteList();
  ~RouteList();
  
  bool addRoute(const std::string &name, const std::string &srcObject, const std::string &destObject);
  bool setRoute(const std::string &name, const std::string &srcObject, const std::string &destObject);

  Route *getRouteByName(const std::string &name) const ;
  Route *getRouteBySouceObject(const std::string &srcObject) const ;
  Route *getRouteBySouceMethod(const std::string &srcMethod) const ;
};

class RouteEngine : public RouteList {
    
public:
    
  RouteEngine();
  virtual ~RouteEngine();
};

class RouteManager : public RouteEngine {
    
 public:
  
  RouteManager();
  virtual ~RouteManager();
};

}

#endif
