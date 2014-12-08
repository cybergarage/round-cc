/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTSCRIPT_H_
#define _ROUNDCC_TESTSCRIPT_H_

#include <round/core/Script.h>

#include "RoundTest.h"

namespace Round {
 
namespace Test {

const std::string JS_ECHO = \
  "function echo(params) {"\
  "  return params;"\
  "}";

const std::string JS_SUM = \
  "function sum(params) {"\
  "  var sum = 0;"
  "  for (i = 0; i < params.length; i++) {"
  "    sum += params[i];"
  "  }"
  "  return sum;"\
  "}";
}
  
}



#endif
