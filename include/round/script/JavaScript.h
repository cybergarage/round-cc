/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_JAVASCRIPT_H_
#define _ROUNDCC_SCRIPT_JAVASCRIPT_H_

#include <round/core/Script.h>

#if defined(ROUND_SUPPORT_JS_SM)
#include <js/jsapi.h>
#endif

namespace Round {

class JavaScriptEngine : public ScriptEngine {
  
 public:
  
  static const std::string LANGUAGE;
  
 public:
  JavaScriptEngine();
  ~JavaScriptEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const std::string &params, std::string *results, Error *error) const;

 private:

  void init();
  void finalize();
  bool getSourceCode(const Script *script, const std::string &params, std::string *sourceCode) const;
  bool run(const std::string &source, std::string *results, Error *error) const;

#if defined(ROUND_SUPPORT_JS_SM)
  JSRuntime *rt;
  JSContext *cx;
  JSObject  *glob;
#endif
  
};
  
}

#endif