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

namespace Round {

static JavaScriptEngine gJavaScriptEngine;

}

Round::JavaScript::JavaScript() {
}

Round::JavaScript::~JavaScript() {
}

bool Round::JavaScript::run() {
  return true;
}