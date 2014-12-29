/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>
#include <round/core/impl/Java.h>
#include <round/core/impl/JavaScript.h>
#include <round/core/SystemMethod.h>

const std::string Round::LocalNodeScriptManager::SYSTEM_ECHO_METHOD_CODE = "function _echo(params) {return params;}";
const std::string Round::LocalNodeScriptManager::SYSTEM_ECHO_METHOD_LANGUAGE = JavaScriptEngine::LANGUAGE;

Round::LocalNodeScriptManager::LocalNodeScriptManager() {
  init();
}

Round::LocalNodeScriptManager::~LocalNodeScriptManager() {
}

void Round::LocalNodeScriptManager::init() {
  Error error;
  
  // Default Script Engine
  setEngine(new JavaEngine());
  setEngine(new JavaScriptEngine());

  // Default Dynamic System Method
  setScript(Round::SystemMethodRequest::ECHO, SYSTEM_ECHO_METHOD_LANGUAGE, SYSTEM_ECHO_METHOD_CODE, Script::ENCODING_NONE, &error);
}
