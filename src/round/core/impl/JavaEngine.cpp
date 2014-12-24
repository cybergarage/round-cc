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

#include <round/common/Base64.h>
#include <round/core/Log.h>
#include <round/core/impl/Java.h>

#define ROUND_UES_JVMOPTIONS 1

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
  if (!this->jniEnv)
    return false;

  jclass loaderClass = this->jniEnv->FindClass("java/lang/ClassLoader");
  if(!loaderClass)
    return false;
  
  jmethodID sysLoaderMethod = this->jniEnv->GetStaticMethodID(loaderClass, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
  if(!sysLoaderMethod)
    return false;
  
  jobject loader = this->jniEnv->CallStaticObjectMethod(loaderClass, sysLoaderMethod);
  jobject globalLoader = this->jniEnv->NewGlobalRef(loader);
  
  std::string scriptName = script->getName();
  std::string scriptCode = script->getCode();
  
  char *classBytes;
  ssize_t classByteLen = Base64::Decode(scriptCode, &classBytes);
  if (classByteLen <= 0)
    return false;
  
  jclass clazz = this->jniEnv->DefineClass(scriptName.c_str(), globalLoader, (jbyte *)classBytes, (jsize)classByteLen);
  this->jniEnv->DeleteGlobalRef(globalLoader);
  
  free(classBytes);
  
  return clazz ? true : false;
}

bool Round::JavaEngine::run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) const {
  if (!this->jniEnv)
    return false;
  
  std::string scriptName = script->getName();
  jclass clazz = this->jniEnv->FindClass(scriptName.c_str());
  if (!clazz)
    return false;
  
  jmethodID initMethodID	= this->jniEnv->GetMethodID(clazz, "<init>",	"()V");
  jmethodID runMethodId      = this->jniEnv->GetMethodID(clazz, "run",	"(Ljava/lang/String;)V");
  if (!initMethodID || !runMethodId)
    return false;
  
  jobject scriptObject = this->jniEnv->NewObject(clazz, initMethodID);
  jstring jstringParams = this->jniEnv->NewStringUTF(params.c_str());
  jstring jstringResults = (jstring)this->jniEnv->CallObjectMethod(scriptObject, runMethodId, jstringParams);
  
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
