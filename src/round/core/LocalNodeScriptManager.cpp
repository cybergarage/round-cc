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

Round::LocalNodeScriptManager::LocalNodeScriptManager() {
  init();
}

Round::LocalNodeScriptManager::~LocalNodeScriptManager() {
}

void Round::LocalNodeScriptManager::init() {
  setEngine(new JavaEngine());
  setEngine(new JavaScriptEngine());
}
