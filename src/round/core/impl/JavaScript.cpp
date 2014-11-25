/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/impl/JavaScript.h>
#include <round/common/Mutex.h>

Round::JavaScript::JavaScript() {
}

Round::JavaScript::JavaScript(const ScriptName &name, const ScriptContent &content) : Script(name, content) {
}

Round::JavaScript::~JavaScript() {
}
