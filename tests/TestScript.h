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

const std::string SCRIPT_ECHO_NAME = "echo";
const std::string SCRIPT_SUM_NAME = "sum";
const std::string SCRIPT_SETCOUNTER_NAME = "set_counter";
const std::string SCRIPT_INCREMENTCOUNTER_NAME = "increment_counter";
const std::string SCRIPT_GETCOUNTER_NAME = "get_counter";

const std::string JS_ECHO_CODE = \
  "function echo(params) {"\
  "  return params;"\
  "}";

const std::string JS_SUM_CODE = \
  "function sum(params) {"\
  "  var sum = 0;"\
  "  for (i = 0; i < params.length; i++) {"\
  "    sum += params[i];"\
  "  }"\
  "  return sum;"\
  "}";

const std::string JS_SETCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function set_counter(params) {"\
  "  global.counter = params;"\
  "  return global.counter;"\
  "}";
  
const std::string JS_INCREMENTCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function increment_counter(params) {"\
  "  global.counter++;"\
  "  return global.counter;"\
  "}";
  
const std::string JS_GETCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function get_counter(params) {"\
  "  return global.counter;"\
  "}";
  
const std::string JAVA_ECHO_SOURCE = "round/tests/scripts/echo.java";
const std::string JAVA_ECHO_CODE = "yv66vgAAADIADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEAA3J1bgEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEACWVjaG8uamF2YQwABAAFAQAEZWNobwEAEGphdmEvbGFuZy9PYmplY3QAIQACAAMAAAAAAAIAAQAEAAUAAQAGAAAAIQABAAEAAAAFKrcAAbEAAAABAAcAAAAKAAIAAAACAAQAAwABAAgACQABAAYAAAAaAAEAAgAAAAIrsAAAAAEABwAAAAYAAQAAAAUAAQAKAAAAAgAL";

const std::string JAVA_SUM_SOURCE = "round/tests/scripts/sum.java";
const std::string JAVA_SUM_CODE = "yv66vgAAADIAKQoACQAXBwAYCAAZCgACABoHABsKABwAHQoAAgAeBwAfBwAgAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEAA3J1bgEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQANU3RhY2tNYXBUYWJsZQcAHwcAGAcAIQcAGwEAClNvdXJjZUZpbGUBAAhzdW0uamF2YQwACgALAQAQamF2YS9sYW5nL1N0cmluZwEABlteMC05XQwAIgAjAQATamF2YS9sYW5nL0V4Y2VwdGlvbgcAJAwAJQAmDAAnACgBAANzdW0BABBqYXZhL2xhbmcvT2JqZWN0AQATW0xqYXZhL2xhbmcvU3RyaW5nOwEABXNwbGl0AQAnKExqYXZhL2xhbmcvU3RyaW5nOylbTGphdmEvbGFuZy9TdHJpbmc7AQARamF2YS9sYW5nL0ludGVnZXIBAAhwYXJzZUludAEAFShMamF2YS9sYW5nL1N0cmluZzspSQEAB3ZhbHVlT2YBABUoSSlMamF2YS9sYW5nL1N0cmluZzsAIQAIAAkAAAAAAAIAAQAKAAsAAQAMAAAAIQABAAEAAAAFKrcAAbEAAAABAA0AAAAKAAIAAAAEAAQABQABAA4ADwABAAwAAACnAAMABgAAADYDvQACTSsSA7YABE2nAAROAz4DNgQVBCy+ogAYHSwVBDK4AAZgPqcABToFhAQBp//nHbgAB7AAAgAFAAwADwAFABwAJgApAAUAAgANAAAAJgAJAAAABwAFAAkADAAKABAACwASAAwAHAAOACYADwArAAwAMQARABAAAAAjAAb/AA8AAwcAEQcAEgcAEwABBwAUAP0ABAEBUwcAFAH6AAUAAQAVAAAAAgAW";

const std::string JS_INVALID_FUNCTION = \
  "function echo(params) {"\
  "  return params;";

#define RPC_SET_ECHO_NAME   "echo"
#define RPC_SET_ECHO_LANG   "js"
#define RPC_SET_ECHO_CODE   "function echo(params) {return params;}"
#define RPC_SET_ECHO_PARAMS "[1,2,3]"
  
const std::string RPC_SET_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"_set_method\","
   "\"params\": {" \
       "\"language\": \"" RPC_SET_ECHO_LANG "\", " \
       "\"name\": \"" RPC_SET_ECHO_NAME "\", " \
       "\"code\": \"" RPC_SET_ECHO_CODE "\"" \
   "}, \"id\": 1}";

const std::string RPC_REMOVE_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"_set_method\","
  "\"params\": {" \
  "\"language\": \"" RPC_SET_ECHO_LANG "\", " \
  "\"name\": \"" RPC_SET_ECHO_NAME "\"" \
  "}, \"id\": 1}";
  
const std::string RPC_RUN_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
   "\"params\": " RPC_SET_ECHO_PARAMS "," \
   "\"id\": 1}";

const std::string RPC_SET_SETMETHOD = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"_set_method\","
  "\"params\": {" \
  "\"language\": \"" RPC_SET_ECHO_LANG "\", " \
  "\"name\": \"_set_method\", " \
  "\"code\": \"" RPC_SET_ECHO_CODE "\"" \
  "}, \"id\": 1}";

class ScriptTestController {
 public:
    
  ScriptTestController() {
  }
    
  void runEchoMethodTest(Round::ScriptManager *scriptMgr);
  void runSumMethodTest(Round::ScriptManager *scriptMgr);
  void runCounterMethodTest(Round::ScriptManager *scriptMgr);
};

}

}

#endif
