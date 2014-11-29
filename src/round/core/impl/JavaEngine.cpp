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

Round::JavaEngine::JavaEngine() : ScriptEngine(Java::LANGUAGE) {
  JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
  JavaVMOption* options = new JavaVMOption[1];
#if defined(ROUND_UES_JVMOPTIONS)
  vm_args.version = JNI_VERSION_1_6;
  vm_args.nOptions = 1;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = false;
#endif
  
  /* load and initialize a Java VM, return a JNI interface pointer in env */
  JNI_CreateJavaVM(&this->jvm, (void**)&this->jniEnv, &vm_args);
  
  delete options;
}

bool Round::JavaEngine::run(const Script *jsScript, const ScriptParams &params, ScriptResults *results, Error *error) const {
  jclass clazz = this->jniEnv->FindClass("Script");
  
  jmethodID initMethodID	= this->jniEnv->GetMethodID(clazz, "<init>",	"()V");
  jmethodID methodId      = this->jniEnv->GetMethodID(clazz, "run",	"(Ljava/lang/String;)V");
  
  jobject scriptObject = this->jniEnv->NewObject(clazz, initMethodID);
  
  jstring jstringResults = (jstring)this->jniEnv->CallObjectMethod(scriptObject, methodId);
  const char* stringResults = this->jniEnv->GetStringUTFChars(jstringResults, NULL);
  *results = stringResults;
  this->jniEnv->ReleaseStringUTFChars(jstringResults, stringResults);
  
  return true;
}

Round::JavaEngine::~JavaEngine() {
  this->jvm->DestroyJavaVM();
}
