/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTSCRIPT_H_
#define _ROUNDCC_TESTSCRIPT_H_

#include <round/Const.h>
#include <round/core/Script.h>

#include "RoundTest.h"

namespace Round {
 
namespace Test {

const std::string SCRIPT_ECHO_NAME = "echo";
const std::string SCRIPT_SUM_NAME = "sum";
const std::string SCRIPT_COUNTER_NAME = "Counter"; // Only Java Platform
const std::string SCRIPT_SETCOUNTER_NAME = "set_counter";
const std::string SCRIPT_INCCOUNTER_NAME = "inc_counter";
const std::string SCRIPT_GETCOUNTER_NAME = "get_counter";

////////////////////////////////////////////////////////////
// JavaScript
////////////////////////////////////////////////////////////

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
  "function inc_counter(params) {"\
  "  global.counter++;"\
  "  return global.counter;"\
  "}";
  
const std::string JS_GETCOUNTER_CODE = \
  "var global = new Function(\"return this\")();"\
  "function get_counter(params) {"\
  "  return global.counter;"\
  "}";
  
////////////////////////////////////////////////////////////
// Java
////////////////////////////////////////////////////////////

const std::string JAVA_ECHO_SOURCE = "round/tests/scripts/echo.java";
const std::string JAVA_ECHO_CODE = "yv66vgAAADIADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAApTb3VyY2VGaWxlAQAJZWNoby5qYXZhDAAEAAUBAARlY2hvAQAQamF2YS9sYW5nL09iamVjdAAhAAIAAwAAAAAAAgABAAQABQABAAYAAAAhAAEAAQAAAAUqtwABsQAAAAEABwAAAAoAAgAAAAIABAADAAEACAAJAAEABgAAABoAAQACAAAAAiuwAAAAAQAHAAAABgABAAAABQABAAoAAAACAAs=";

const std::string JAVA_SUM_SOURCE = "round/tests/scripts/sum.java";
const std::string JAVA_SUM_CODE = "yv66vgAAADIAKQoACQAXBwAYCAAZCgACABoHABsKABwAHQoAAgAeBwAfBwAgAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAA1TdGFja01hcFRhYmxlBwAfBwAYBwAhBwAbAQAKU291cmNlRmlsZQEACHN1bS5qYXZhDAAKAAsBABBqYXZhL2xhbmcvU3RyaW5nAQAGW14wLTldDAAiACMBABNqYXZhL2xhbmcvRXhjZXB0aW9uBwAkDAAlACYMACcAKAEAA3N1bQEAEGphdmEvbGFuZy9PYmplY3QBABNbTGphdmEvbGFuZy9TdHJpbmc7AQAFc3BsaXQBACcoTGphdmEvbGFuZy9TdHJpbmc7KVtMamF2YS9sYW5nL1N0cmluZzsBABFqYXZhL2xhbmcvSW50ZWdlcgEACHBhcnNlSW50AQAVKExqYXZhL2xhbmcvU3RyaW5nOylJAQAHdmFsdWVPZgEAFShJKUxqYXZhL2xhbmcvU3RyaW5nOwAhAAgACQAAAAAAAgABAAoACwABAAwAAAAhAAEAAQAAAAUqtwABsQAAAAEADQAAAAoAAgAAAAQABAAFAAEADgAPAAEADAAAAKcAAwAGAAAANgO9AAJNKxIDtgAETacABE4DPgM2BBUELL6iABgdLBUEMrgABmA+pwAFOgWEBAGn/+cduAAHsAACAAUADAAPAAUAHAAmACkABQACAA0AAAAmAAkAAAAHAAUACQAMAAoAEAALABIADAAcAA4AJgAPACsADAAxABEAEAAAACMABv8ADwADBwARBwASBwATAAEHABQA/QAEAQFTBwAUAfoABQABABUAAAACABY=";

const std::string JAVA_COUNTER_SOURCE = "round/tests/scripts/Counter.java";
const std::string JAVA_COUNTER_CODE = "yv66vgAAADIAFwoABAATCQADABQHABUHABYBAAV2YWx1ZQEAAUkBAAY8aW5pdD4BAAMoKVYBAARDb2RlAQAPTGluZU51bWJlclRhYmxlAQAKU2V0Q291bnRlcgEABChJKVYBABBJbmNyZW1lbnRDb3VudGVyAQAKR2V0Q291bnRlcgEAAygpSQEACDxjbGluaXQ+AQAKU291cmNlRmlsZQEADENvdW50ZXIuamF2YQwABwAIDAAFAAYBAAdDb3VudGVyAQAQamF2YS9sYW5nL09iamVjdAAxAAMABAAAAAEACQAFAAYAAAAFAAEABwAIAAEACQAAAB0AAQABAAAABSq3AAGxAAAAAQAKAAAABgABAAAAAQApAAsADAABAAkAAAAhAAEAAQAAAAUaswACsQAAAAEACgAAAAoAAgAAAAYABAAHACkADQAIAAEACQAAACUAAgAAAAAACbIAAgRgswACsQAAAAEACgAAAAoAAgAAAAoACAALACkADgAPAAEACQAAABwAAQAAAAAABLIAAqwAAAABAAoAAAAGAAEAAAAOAAgAEAAIAAEACQAAAB0AAQAAAAAABQOzAAKxAAAAAQAKAAAABgABAAAAAwABABEAAAACABI=";

const std::string JAVA_SETCOUNTER_SOURCE = "round/tests/scripts/set_counter.java";
const std::string JAVA_SETCOUNTER_CODE = "yv66vgAAADIAJQoABwASCgATABQJABUAFgcAFwoAGAAZBwAaBwAbAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAA1TdGFja01hcFRhYmxlBwAXAQAKU291cmNlRmlsZQEAEHNldF9jb3VudGVyLmphdmEMAAgACQcAHAwAHQAeBwAfDAAgACEBABNqYXZhL2xhbmcvRXhjZXB0aW9uBwAiDAAjACQBAAtzZXRfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBABFqYXZhL2xhbmcvSW50ZWdlcgEACHBhcnNlSW50AQAVKExqYXZhL2xhbmcvU3RyaW5nOylJAQAHQ291bnRlcgEABXZhbHVlAQABSQEAEGphdmEvbGFuZy9TdHJpbmcBAAd2YWx1ZU9mAQAVKEkpTGphdmEvbGFuZy9TdHJpbmc7ACEABgAHAAAAAAACAAEACAAJAAEACgAAACEAAQABAAAABSq3AAGxAAAAAQALAAAACgACAAAABQAEAAYAAQAMAA0AAQAKAAAATQABAAMAAAAUK7gAAj0cswADpwAETbIAA7gABbAAAQAAAAkADAAEAAIACwAAABIABAAAAAoABQALAAkADAANAA4ADgAAAAcAAkwHAA8AAAEAEAAAAAIAEQ==";

const std::string JAVA_GETCOUNTER_SOURCE = "round/tests/scripts/get_counter.java";
const std::string JAVA_GETCOUNTER_CODE = "yv66vgAAADIAGwoABQAOCQAPABAKABEAEgcAEwcAFAEABjxpbml0PgEAAygpVgEABENvZGUBAA9MaW5lTnVtYmVyVGFibGUBAA5wcm9jZXNzTWVzc2FnZQEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEAEGdldF9jb3VudGVyLmphdmEMAAYABwcAFQwAFgAXBwAYDAAZABoBAAtnZXRfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBAAdDb3VudGVyAQAFdmFsdWUBAAFJAQAQamF2YS9sYW5nL1N0cmluZwEAB3ZhbHVlT2YBABUoSSlMamF2YS9sYW5nL1N0cmluZzsAIQAEAAUAAAAAAAIAAQAGAAcAAQAIAAAAIQABAAEAAAAFKrcAAbEAAAABAAkAAAAKAAIAAAAFAAQABgABAAoACwABAAgAAAAfAAEAAgAAAAeyAAK4AAOwAAAAAQAJAAAABgABAAAACQABAAwAAAACAA0=";

const std::string JAVA_INCCOUNTER_SOURCE = "round/tests/scripts/inc_counter.java";
const std::string JAVA_INCCOUNTER_CODE = "yv66vgAAADIAGwoABQAOCQAPABAKABEAEgcAEwcAFAEABjxpbml0PgEAAygpVgEABENvZGUBAA9MaW5lTnVtYmVyVGFibGUBAA5wcm9jZXNzTWVzc2FnZQEAJihMamF2YS9sYW5nL1N0cmluZzspTGphdmEvbGFuZy9TdHJpbmc7AQAKU291cmNlRmlsZQEAEGluY19jb3VudGVyLmphdmEMAAYABwcAFQwAFgAXBwAYDAAZABoBAAtpbmNfY291bnRlcgEAEGphdmEvbGFuZy9PYmplY3QBAAdDb3VudGVyAQAFdmFsdWUBAAFJAQAQamF2YS9sYW5nL1N0cmluZwEAB3ZhbHVlT2YBABUoSSlMamF2YS9sYW5nL1N0cmluZzsAIQAEAAUAAAAAAAIAAQAGAAcAAQAIAAAAIQABAAEAAAAFKrcAAbEAAAABAAkAAAAKAAIAAAAFAAQABgABAAoACwABAAgAAAArAAIAAgAAAA+yAAIEYLMAArIAArgAA7AAAAABAAkAAAAKAAIAAAAJAAgACgABAAwAAAACAA0=";

////////////////////////////////////////////////////////////
// Lua
////////////////////////////////////////////////////////////

const std::string LUA_ECHO_CODE = \
"function echo(params)\n"\
"  return params\n"\
"end";
  
const std::string LUA_SUM_CODE = \
"function sum(jsonParams)\n"\
"  local json = require(\"json\")\n"\
"  local params = json.decode(jsonParams)\n"\
"  local sum = 0\n"\
"  for i, value in pairs(params) do\n"\
"  sum = sum + value\n"\
"  end\n"\
"  return sum\n"\
"  end\n";
  
////////////////////////////////////////////////////////////
// Method Requests
////////////////////////////////////////////////////////////

const std::string JS_INVALID_FUNCTION = \
  "function echo(params) {"\
  "  return params;";

#define RPC_SET_ECHO_NAME   "echo"
#define RPC_ALIAS_HELLO_NAME "hello"
#define RPC_SET_ECHO_LANG   "js"
#define RPC_SET_ECHO_CODE   "function echo(params) {return params;}"
#define RPC_SET_ECHO_PARAMS "[1,2,3]"

////////////////////////////////////////////////
// set_method
////////////////////////////////////////////////

const std::string RPC_SET_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"" ROUNDCC_SYSTEM_METHOD_SET_METHOD "\","
   "\"params\": {" \
       "\"language\": \"" RPC_SET_ECHO_LANG "\", " \
       "\"name\": \"" RPC_SET_ECHO_NAME "\", " \
       "\"code\": \"" RPC_SET_ECHO_CODE "\"" \
   "}, \"id\": 1}";

const std::string RPC_REMOVE_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_REMOVE_METHOD "\","
  "\"params\": {" \
  "\"name\": \"" RPC_SET_ECHO_NAME "\"" \
  "}, \"id\": 1}";
  
const std::string RPC_RUN_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
   "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
   "\"params\": " RPC_SET_ECHO_PARAMS "," \
   "\"id\": 1}";

////////////////////////////////////////////////
// Alias (Hello)
////////////////////////////////////////////////
  
const std::string RPC_SET_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_SET_ALIAS "\","
  "\"params\": {" \
    "\"name\": \"" RPC_ALIAS_HELLO_NAME "\", " \
    "\"method\": \"" RPC_SET_ECHO_NAME "\", " \
    "\"defaults\": \"" RPC_SET_ECHO_PARAMS "\"" \
  "}, \"id\": 1}";
  
const std::string RPC_REMOVE_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_REMOVE_ALIAS "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ALIAS_HELLO_NAME "\"" \
  "}, \"id\": 1}";
  
const std::string RPC_RUN_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_ALIAS_HELLO_NAME "\"," \
  "\"id\": 1}";

////////////////////////////////////////////////
// Route (Hello)
////////////////////////////////////////////////

#define RPC_ECHO_HELLO_NAME   "echo_hello"
#define RPC_ECHO_HELLO_LANG   "js"
#define RPC_ECHO_HELLO_PREFIX   "Hello "
#define RPC_ECHO_HELLO_CODE   "function " RPC_ECHO_HELLO_NAME "(params) {return '" RPC_ECHO_HELLO_PREFIX "'+ params;}"
#define RPC_ECHO_HELLO_PARAM "Round"

const std::string RPC_SET_ECHO_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_SET_METHOD "\","
  "\"params\": {" \
  "\"language\": \"" RPC_ECHO_HELLO_LANG "\", " \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\", " \
  "\"code\": \"" RPC_ECHO_HELLO_CODE "\"" \
  "}, \"id\": 1}";

const std::string RPC_REMOVE_ECHO_HELLO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_REMOVE_METHOD "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

const std::string RPC_SET_ECHO_HELLO_ROUTE = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_SET_ROUTE "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"," \
  "\"src\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"dest\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

const std::string RPC_REMOVE_ECHO_HELLO_ROUTE = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" ROUNDCC_SYSTEM_METHOD_REMOVE_ROUTE "\","
  "\"params\": {" \
  "\"name\": \"" RPC_ECHO_HELLO_NAME "\"" \
  "}, \"id\": 1}";

const std::string RPC_RUN_ROUTE_ECHO = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": \"" RPC_ECHO_HELLO_PARAM "\"," \
  "\"id\": 1}";
  
////////////////////////////////////////////////
// RPC
////////////////////////////////////////////////

const std::string RPC_RUN_BATCH_ECHO = \
  "[" \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": " RPC_SET_ECHO_PARAMS "," \
  "\"id\": 1},"
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"" RPC_SET_ECHO_NAME "\"," \
  "\"params\": " RPC_SET_ECHO_PARAMS "," \
  "\"id\": 1}" \
  "]";
  
const std::string RPC_SET_SETMETHOD = \
  "{\"jsonrpc\": \"2.0\"," \
  "\"method\": \"set_method\","
  "\"params\": {" \
  "\"language\": \"" RPC_SET_ECHO_LANG "\", " \
  "\"name\": \"set_method\", " \
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
