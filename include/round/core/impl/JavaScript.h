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

#include <v8.h>
#include <round/core/Script.h>

namespace Round {

class JavaScript : public Script {

 public:
  JavaScript();
  virtual ~JavaScript();

  bool run();
  
};

class JavaScriptEngine : public ScriptEngine {
    
 public:
  JavaScriptEngine();
  virtual ~JavaScriptEngine();
  
  bool run(Script *script, const std::string &params, std::string *results, Error *error);

 private:

  bool run(const std::string &source, std::string *results, Error *error);
};
  
}

#endif
