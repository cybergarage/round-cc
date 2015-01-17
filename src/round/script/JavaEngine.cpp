/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

#include <round/common/encoding/Base64.h>
#include <round/core/Log.h>
#include <round/script/Java.h>

#if defined(ROUND_SUPPORT_JAVA_JNI)

#undef ROUND_USE_JVMOPTIONS_VERBOSE

#if defined(__APPLE__)
#include <JavaVM/jni.h>
#else
#include <jni.h>
#endif

////////////////////////////////////////////////
// Static methods
////////////////////////////////////////////////

namespace Round {
  
static bool IsJavaVMInitialized = false;
  
static JavaVM *gJavaVM = NULL;
static JNIEnv *gJNIEnv = NULL;

static void JavaEngineExit(void) {
  if (gJavaVM) {
    gJavaVM->DestroyJavaVM();
  }
}
  
}

const std::string Round::JavaEngine::LANGUAGE = "java";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::JavaEngine::JavaEngine() : ScriptEngine(LANGUAGE) {
  if (!IsJavaVMInitialized) {
    JavaVMInitArgs vm_args;
    JNI_GetDefaultJavaVMInitArgs(&vm_args);
    vm_args.ignoreUnrecognized = false;;
    vm_args.nOptions = 0;
#if defined(ROUND_USE_JVMOPTIONS_VERBOSE)
    vm_args.nOptions++;
#endif
  
    JavaVMOption* options = new JavaVMOption[vm_args.nOptions];
#if defined(ROUND_USE_JVMOPTIONS_VERBOSE)
    options[0].optionString = const_cast<char*>("-verbose:class");
#endif
    vm_args.version = JNI_VERSION_1_6;
    vm_args.options = options;
  
    JNI_CreateJavaVM(&gJavaVM, (void**)&gJNIEnv, &vm_args);
  
    delete options;
    
    IsJavaVMInitialized = true;
    atexit(JavaEngineExit);
  }
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Round::JavaEngine::~JavaEngine() {
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Round::JavaEngine::compile(const Script *script) const {
  if (!gJNIEnv)
    return false;

  jclass loaderClass = gJNIEnv->FindClass("java/lang/ClassLoader");
  if(!loaderClass)
    return false;
  
  jmethodID sysLoaderMethod = gJNIEnv->GetStaticMethodID(loaderClass, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
  if(!sysLoaderMethod)
    return false;
  
  jobject loader = gJNIEnv->CallStaticObjectMethod(loaderClass, sysLoaderMethod);
  jobject globalLoader = gJNIEnv->NewGlobalRef(loader);
  
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
  
  jclass clazz = gJNIEnv->DefineClass(scriptName.c_str(), globalLoader, (jbyte *)scriptBytes, (jsize)scriptByteLen);
  
  gJNIEnv->DeleteGlobalRef(globalLoader);
  
  if (decordedScriptBytes)
    free(decordedScriptBytes);
  
  return clazz ? true : false;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::JavaEngine::run(const Script *script, const std::string &params, std::string *results, Error *error) const {
  if (!gJNIEnv)
    return false;
  
  std::string scriptName = script->getName();
  jclass clazz = gJNIEnv->FindClass(scriptName.c_str());
  if (!clazz)
    return false;
  
  jmethodID initMethodID = gJNIEnv->GetMethodID(clazz, "<init>",	"()V");
  jmethodID runMethodId  = gJNIEnv->GetMethodID(clazz, "processMessage",	"(Ljava/lang/String;)Ljava/lang/String;");
  if (!initMethodID || !runMethodId)
    return false;
  
  jobject scriptObject = gJNIEnv->NewObject(clazz, initMethodID);
  jstring jstringParams = gJNIEnv->NewStringUTF(params.c_str());
  jstring jstringResults = (jstring)gJNIEnv->CallObjectMethod(scriptObject, runMethodId, jstringParams);
  if (jstringResults) {
    const char* stringResults = gJNIEnv->GetStringUTFChars(jstringResults, NULL);
    *results = stringResults;
    gJNIEnv->ReleaseStringUTFChars(jstringResults, stringResults);
  }
  
  return true;
}

#endif
