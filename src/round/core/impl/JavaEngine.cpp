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

const std::string Round::JavaEngine::LANGUAGE = "java";

Round::JavaEngine::JavaEngine() : ScriptEngine(LANGUAGE) {
  JavaVMInitArgs vm_args;
  vm_args.ignoreUnrecognized = false;
  vm_args.nOptions = 1;
  
#if defined(ROUND_UES_JVMOPTIONS)
  JavaVMOption* options = new JavaVMOption[vm_args.nOptions];
  options[0].optionString = const_cast<char*>("-verbose:jni");
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
  
  const byte *scriptBytes = NULL;
  size_t scriptByteLen = 0;
  byte *decordedScriptBytes = NULL;
  
  if (!script->isEncoded()) {
    scriptBytes = script->getCode();
    scriptByteLen = script->getCodeLength();
  } else if (script->isBase64Encoded()) {
    std::string scriptCode = script->getStringCode();
    scriptByteLen = Base64::Decode(scriptCode, &decordedScriptBytes);
    if (scriptByteLen <= 0)
      return false;
    scriptBytes = decordedScriptBytes;
  }
  
  jclass clazz = this->jniEnv->DefineClass(scriptName.c_str(), globalLoader, (jbyte *)scriptBytes, (jsize)scriptByteLen);
  
  this->jniEnv->DeleteGlobalRef(globalLoader);
  
  if (decordedScriptBytes)
    free(decordedScriptBytes);
  
  return clazz ? true : false;
}

bool Round::JavaEngine::run(const Script *script, const std::string &params, std::string *results, Error *error) const {
  if (!this->jniEnv)
    return false;
  
  std::string scriptName = script->getName();
  jclass clazz = this->jniEnv->FindClass(scriptName.c_str());
  if (!clazz)
    return false;
  
  jmethodID initMethodID	= this->jniEnv->GetMethodID(clazz, "<init>",	"()V");
  jmethodID runMethodId      = this->jniEnv->GetMethodID(clazz, "run",	"(Ljava/lang/String;)Ljava/lang/String;");
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
