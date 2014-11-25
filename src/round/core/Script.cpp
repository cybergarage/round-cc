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

Round::Script::Script() {
}

Round::Script::Script(const ScriptName &name, const ScriptContent &content) {
  setName(name);
  setContent(content);
}

Round::Script::~Script() {
}
