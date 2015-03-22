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

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

BOOST_AUTO_TEST_CASE(LuaEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, LuaEngine::LANGUAGE, Round::Test::JS_ECHO_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(LuaEngineSumTest) {
  
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new Script(LuaEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::JS_SUM_CODE)));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_SUITE_END()

