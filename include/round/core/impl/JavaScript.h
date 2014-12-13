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

class JavaScriptEngine : public ScriptEngine {
  
 public:
  
  static const ScriptName LANGUAGE;
  static size_t GetInstanceCount();
  
 public:
  JavaScriptEngine();
  ~JavaScriptEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) const;

 private:

  void init();
  bool run(const std::string &source, std::string *results, Error *error) const;

 private:
  v8::Isolate *isolate;
};
  
}

#endif
