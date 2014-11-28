/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Script.h>

Round::ScriptEngine::ScriptEngine(const ScriptLang &language) {
  this->language = language;
}

Round::ScriptEngine::~ScriptEngine() {
}
