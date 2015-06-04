/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Script.h>

Round::ScriptEngine::ScriptEngine(const std::string &language) {
  init();
  this->language = language;
}

void Round::ScriptEngine::init() {
  setNode(NULL);
}

Round::ScriptEngine::~ScriptEngine() {
}
