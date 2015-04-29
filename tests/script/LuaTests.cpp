/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <vector>
#include <round/script/Lua.h>

#include "TestScript.h"
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

////////////////////////////////////////////////////////////
// Lua Engine
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(LuaEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, LuaEngine::LANGUAGE, Round::Test::LUA_ECHO_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(LuaEngineSumTest) {
  
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new Script(LuaEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::LUA_SUM_CODE)));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(&scriptMgr);
}

////////////////////////////////////////////////////////////
// Lua Function
////////////////////////////////////////////////////////////

#define LUA_JOB_SCRIPT_BUF_SIZE 1024

#define LUA_TEST_JOB_HELLO "hello"
#define LUA_TEST_JOB_HELLO_SCRIPT \
"return \"" LUA_TEST_JOB_HELLO "\""
   
BOOST_AUTO_TEST_CASE(LuaHelloTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, LUA_TEST_JOB_HELLO_SCRIPT, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare(LUA_TEST_JOB_HELLO), 0);
  
  BOOST_CHECK(node.stop(&err));
}

BOOST_AUTO_TEST_SUITE_END()
