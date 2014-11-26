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

Round::Script::Script(const ScriptLanguage &language) {
  this->language = language;
}

Round::Script::Script(const ScriptName &name, const ScriptContent &content) {
  setName(name);
  setContent(content);
}

Round::Script::~Script() {
}
