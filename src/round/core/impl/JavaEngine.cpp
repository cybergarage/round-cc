/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

#include <round/core/Log.h>
#include <round/core/impl/Java.h>

const Round::ScriptName Round::JavaEngine::LANGUAGE = "java";

Round::JavaEngine::JavaEngine() : ScriptEngine(LANGUAGE) {
  JavaVMInitArgs vm_args;
  vm_args.ignoreUnrecognized = false;
  vm_args.nOptions = 0  ;
  
#if defined(ROUND_UES_JVMOPTIONS)
  JavaVMOption* options = new JavaVMOption[1];
  vm_args.version = JNI_VERSION_1_6;
  vm_args.options = options;
#endif
  
  JNI_CreateJavaVM(&this->jvm, (void**)&this->jniEnv, &vm_args);
  
#if defined(ROUND_UES_JVMOPTIONS)
  delete options;
#endif
}

bool Round::JavaEngine::compile(const Script *script) const {
  return true;
}

bool Round::JavaEngine::run(const Script *jsScript, const ScriptParams &params, ScriptResults *results, Error *error) const {
  jclass clazz = this->jniEnv->FindClass("Script");
  
  jmethodID initMethodID	= this->jniEnv->GetMethodID(clazz, "<init>",	"()V");
  jmethodID methodId      = this->jniEnv->GetMethodID(clazz, "run",	"(Ljava/lang/String;)V");
  
  jobject scriptObject = this->jniEnv->NewObject(clazz, initMethodID);
  
  jstring jstringParams = this->jniEnv->NewStringUTF(params.c_str());
  
  jstring jstringResults = (jstring)this->jniEnv->CallObjectMethod(scriptObject, methodId, jstringParams);
  
  
  const char* stringResults = this->jniEnv->GetStringUTFChars(jstringResults, NULL);
  *results = stringResults;
  this->jniEnv->ReleaseStringUTFChars(jstringResults, stringResults);
  
  return true;
}

Round::JavaEngine::~JavaEngine() {
  if (this->jvm) {
    this->jvm->DestroyJavaVM();
  }
}
