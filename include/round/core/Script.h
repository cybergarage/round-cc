/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_H_
#define _ROUNDCC_SCRIPT_H_

#include <vector>

namespace Round {

class Script {

 public:
  Script();
  virtual ~Script();

  virtual bool run() = 0;
  
};

class ScriptList : public std::vector<Script *> {
    
public:
    
  ScriptList();
  virtual ~ScriptList();
  
  void addScript(Script *node) {
    push_back(node);
  }
    
  Script *getScript(size_t index) const {
    return at(index);
  }
};

}

#endif
