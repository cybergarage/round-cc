/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JAVA_H_
#define _ROUNDCC_JAVA_H_

#include <round/core/Script.h>

#if defined(__APPLE__)
#include <JavaVM/jni.h>
#else
#include <jni.h>
#endif

namespace Round {

class JavaEngine : public ScriptEngine {
    
 public:
  
  static const ScriptName LANGUAGE;
  
 public:
  JavaEngine();
  
  ~JavaEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) const;

 private:
  JavaVM *jvm;
  JNIEnv *jniEnv;
};
  
}

#endif
