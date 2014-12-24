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

const std::string JAVA_ECHO_SOURCE = \
  "public class echo {"\
  "  public echo() {"\
  "  }"\
  "  public String run(String params) {"\
  "    return params;"\
  "  }"\
  "}";
  
const std::string JAVA_ECHO_CODE = "yv66vgAAADQADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEAA3J1bgEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEACWVjaG8uamF2YQwABAAFAQAEZWNobwEAEGphdmEvbGFuZy9PYmplY3QAIQACAAMAAAAAAAIAAQAEAAUAAQAGAAAAIQABAAEAAAAFKrcAAbEAAAABAAcAAAAKAAIAAAACAAQAAwABAAgACQABAAYAAAAaAAEAAgAAAAIrsAAAAAEABwAAAAYAAQAAAAUAAQAKAAAAAgAL";
  
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
    
  void runEchoMethodTest(const std::string &scriptName, Round::ScriptManager *scriptMgr);
  void runSumMethodTest(const std::string &scriptName, Round::ScriptManager *scriptMgr);
};

}

}

#endif
