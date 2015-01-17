/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Method.h>

Round::StaticMethodMap::StaticMethodMap() {
}

Round::StaticMethodMap::~StaticMethodMap() {
  clear();
}

bool Round::StaticMethodMap::hasMethod(const std::string &name) const {
  return (find(name) != end()) ? true : false;
}

bool Round::StaticMethodMap::exec(const std::string &name, const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) const {
  StaticMethodMap::const_iterator methodId = find(name);
  if (methodId == end())
    return false;
  Method *method = methodId->second;
  return method->exec(nodeReq, nodeRes, error);
}

void Round::StaticMethodMap::clear() {
  for (StaticMethodMap::iterator methodId = begin(); methodId != end(); methodId++) {
    Method *method = methodId->second;
    if (method)
      delete method;
  }
  
  std::map<std::string, Method *>::clear();
}
