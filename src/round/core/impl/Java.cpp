/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/impl/Java.h>
#include <round/common/Mutex.h>

const std::string Round::Java::LANGUAGE = "java";

Round::Java::Java() : Script(LANGUAGE) {
}

Round::Java::Java(const ScriptName &name, const ScriptContent &content) : Script(LANGUAGE, name, content) {
}

Round::Java::~Java() {
}
