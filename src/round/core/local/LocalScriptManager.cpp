/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>
#include <round/common/platform.h>

#include <round/core/local/method/SystemMethod.h>

#include <round/script/JavaScript.h>
#if defined(ROUND_SUPPORT_JAVA_JNI)
#include <round/script/Java.h>
#endif
#if defined(ROUND_SUPPORT_TCL_JNI)
#include <round/script/Tcl.h>
#endif
#if defined(ROUND_SUPPORT_LUA)
#include <round/script/Lua.h>
#endif

const std::string Round::LocalScriptManager::SYSTEM_ECHO_METHOD_CODE = "function _echo(params) {return params;}";
const std::string Round::LocalScriptManager::SYSTEM_ECHO_METHOD_LANGUAGE = "js"; //JavaScriptEngine::LANGUAGE;

Round::LocalScriptManager::LocalScriptManager() {
  init();
}

Round::LocalScriptManager::~LocalScriptManager() {
}

void Round::LocalScriptManager::init() {
  Error error;
  
  // Default Script Engine
  setEngine(new JavaScriptEngine());
#if defined(ROUND_SUPPORT_JAVA_JNI)
  setEngine(new JavaEngine());
#endif
#if defined(ROUND_SUPPORT_TCL_JNI)
  setEngine(new TclEngine());
#endif
#if defined                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      (ROUND_SUPPORT_LUA)
  setEngine(new LuaEngine());
#endif
  
  // Default Dynamic System Method
  setScript(Round::system_method::ECHO, SYSTEM_ECHO_METHOD_LANGUAGE, SYSTEM_ECHO_METHOD_CODE, Script::ENCODING_NONE, &error);
}
