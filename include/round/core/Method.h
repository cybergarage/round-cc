/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_METHOD_H_
#define _ROUNDCC_METHOD_H_

#include <string>
#include <round/core/NodeMessage.h>

namespace Round {

class LocalNode;
  
class Method {

 public:
  Method(const std::string &name);
  virtual ~Method();
  
  const std::string &getName() const;
  virtual bool exec(const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) const = 0;

 private:
  std::string name;
};

class StaticMethodMap : public std::map<std::string, Method *> {
    
 public:
    
  StaticMethodMap();
  ~StaticMethodMap();
    
  bool hasMethod(const std::string &name) const;
  bool exec(const std::string &name, const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) const;
  
  void clear();
};

class StaticMethodManager {
    
 public:
    
  StaticMethodManager();
  ~StaticMethodManager();

  bool hasMethod(const std::string &name) const {
    return systemMethods.hasMethod(name);
  }

  bool addMethod(Method *method);
  
  bool exec(const std::string &name, const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) const {
    return systemMethods.exec(name, node, nodeReq, nodeRes, error);
  }
  
 private:
  StaticMethodMap systemMethods;
};
  
}

#endif
