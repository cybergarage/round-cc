/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_JAVA_H_
#define _ROUNDCC_SCRIPT_JAVA_H_

#include <round/core/Script.h>

namespace Round {

class JavaEngine : public ScriptEngine {
    
 public:
  
  static const std::string LANGUAGE;
  
 public:
  JavaEngine();
  
  ~JavaEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const std::string &params, std::string *results, Error *error) const;
};
  
}

#endif
