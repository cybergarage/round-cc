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

Round::StaticMethodManager::StaticMethodManager() {
}

Round::StaticMethodManager::~StaticMethodManager() {
}

bool Round::StaticMethodManager::addMethod(Method *method) {
  if (!method)
    return false;
  
  const std::string methodName = method->getName();
  
  StaticMethodMap::const_iterator methodId = this->systemMethods.find(methodName);
  if (methodId != this->systemMethods.end()) {
    this->systemMethods.erase(methodId);
  }
  
  this->systemMethods[methodName] = method;
  
  return true;
}

