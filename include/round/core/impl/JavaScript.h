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

#include <v8.h>
#if defined(ROUND_V8_USE_LIBPLATFORM)
#include "libplatform/libplatform.h"
#endif

namespace Round {

class JavaScript : public Script {

public:
  static const ScriptName LANGUAGE;
  
 public:
  JavaScript();
  JavaScript(const ScriptName &name, const ScriptContent &content);
  
  virtual ~JavaScript();
};

class JavaScriptEngine : public ScriptEngine {
    
 public:
  JavaScriptEngine();
  
  virtual ~JavaScriptEngine();
  
  bool run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) const;

 private:

  bool run(const std::string &source, std::string *results, Error *error) const;

 private:
  v8::Isolate *isolate;
#if defined(ROUND_V8_USE_LIBPLATFORM)
  v8::Platform *platform;
#endif
};
  
}

#endif
