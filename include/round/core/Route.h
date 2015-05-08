/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
  
  static const int TARGET;
  static const int NODE;
  static const int CLUSTER;
  
public:
  RouteObjects();
  RouteObjects(const std::string &value);
  ~RouteObjects();
  
  bool isValid() const;
  bool parse(const std::string &value);

  bool getObject(int objIdx, std::string *value) const;

  bool getTarget(std::string *value) const {
    return getObject(TARGET, value);
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
  
  bool toString(std::string *value) const;
};
  
class Route {

public:
  
  static const std::string NODE_DEFALUT;
  static const std::string NODE_LOCAL;
  static const std::string NODE_ALL;
  
  static const std::string CLUSTER_DEFALUT;
  static const std::string CLUSTER_LOCAL;
  
  static const std::string METHOD_DEFALUT;

  static const std::string TYPE_EVENT;
  static const std::string TYPE_PIPE;
  
public:
  
  Route();
  Route(const std::string &name, const std::string &srcObj, const std::string &destObj);
  
  virtual ~Route();

  bool isValid();

  // Name
  
  bool setName(const std::string &value);
  bool getName(std::string *value) const;
  bool isName(const std::string &value) const;
  bool hasName() const;
  
  // Source
  
  bool setSource(const std::string &value);

  const RouteObjects &getSourceObjects() const {
    return this->srcObjects;
  }
  
  bool isSource(const std::string &value) const {
    return this->srcObjects.equals(value);
  }
  
  bool getSourceTarget(std::string *value) const {
    return this->srcObjects.getTarget(value);
  }
  
  bool getSourceNode(std::string *value) const {
    return this->srcObjects.getNode(value);
  }
  
  bool getSourceCluster(std::string *value) const {
    return this->srcObjects.getCluster(value);
  }
  
  bool isSourceMethod(const std::string &value) const {
    return this->srcObjects.isMethod(value);
  }
  
  // Destination
  
  bool setDestination(const std::string &value);
  
  const RouteObjects &getDestinationObjects() const {
    return this->destObjects;
  }
  
  bool isDestination(const std::string &value) const {
    return this->destObjects.equals(value);
  }
  
  bool getDestinationTarget(std::string *value) const {
    return this->destObjects.getTarget(value);
  }
  
  bool getDestinationNode(std::string *value) const {
    return this->destObjects.getNode(value);
  }
  
  bool getDestinationCluster(std::string *value) const {
    return this->destObjects.getCluster(value);
  }
  
  bool equals(const Route *otherRoute) const;

  // Type
  
  bool setType(const std::string &value);

  bool hasType() {
    return (0 < this->type.length());
  }

  const std::string *getType() {
    return &this->type;
  }
  
  bool isPipe();
  bool isEvent();
  bool isValidType();

private:
  
  std::string  name;
  RouteObjects srcObjects;
  RouteObjects destObjects;
  std::string type;
};

class RouteList : public Vector<Route> {
    
 public:
  
  RouteList();
  ~RouteList();
  
  bool addRoute(Route *route);
  bool setRoute(Route *route);

  bool addRoute(const std::string &name, const std::string &srcObj, const std::string &destObj);
  bool setRoute(const std::string &name, const std::string &srcObj, const std::string &destObj);
  
  Route *findSameRoute(const Route *otherRoute) const ;
  Route *findRouteByName(const std::string &name) const ;
  Route *findRouteBySouceObject(const std::string &srcObj) const ;
  Route *findRouteBySouceMethod(const std::string &srcMethod) const ;
};

class RouteMap : public std::map<std::string, RouteList *> {
  
public:
  
  RouteMap();
  ~RouteMap();

  bool addRoute(Route *route);
  bool setRoute(Route *route);
  
  bool addRoute(const std::string &name, const std::string &srcObj, const std::string &destObj);
  bool setRoute(const std::string &name, const std::string &srcObj, const std::string &destObj);
  
  Route *findRouteByName(const std::string &name) const ;
  
  void clear();
  
  size_t count();
  
private:
  
  RouteList *getRouteListBySourcePath(const std::string &srcPath);
  RouteList *getRouteListByRoute(Route *route);
};
  
class RouteManager : public RouteMap {
    
 public:
  
  RouteManager();
  virtual ~RouteManager();

  void lock() {
    mutex.lock();
  }
  
  void unlock() {
    mutex.unlock();
  }
  
private:
  
  Mutex mutex;
};

}

#endif
