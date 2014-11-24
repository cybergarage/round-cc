/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JAVASCRIPT_H_
#define _ROUNDCC_JAVASCRIPT_H_

#include <round/core/Script.h>

namespace Round {

class JavaScriptList;
  
class JavaScript : public Script {

 public:
  JavaScript();
  virtual ~JavaScript();

  bool run();
  
};

class JavaScriptList : public std::vector<Script *> {
    
  public:
    
  JavaScriptList();
  virtual ~JavaScriptList();
    
};

class JavaScriptEngine {
    
  public:
    JavaScriptEngine();
    virtual ~JavaScriptEngine();
  };
  
}

#endif
