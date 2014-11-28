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

const std::string Round::JavaScript::LANGUAGE = "js";

Round::JavaScript::JavaScript() : Script(LANGUAGE) {
}

Round::JavaScript::JavaScript(const ScriptName &name, const ScriptContent &content) : Script(LANGUAGE, name, content) {
}

Round::JavaScript::~JavaScript() {
}
