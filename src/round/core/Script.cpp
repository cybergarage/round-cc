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

Round::Script::Script(const ScriptLang &lang) {
  this->language = lang;
}

Round::Script::Script(const ScriptLang &lang, const ScriptName &name, const ScriptContent &content) {
  this->language = lang;
  setName(name);
  setContent(content);
}

Round::Script::~Script() {
}
