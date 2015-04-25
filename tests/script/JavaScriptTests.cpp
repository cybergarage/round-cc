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
#include <round/script/JavaScript.h>

#include "TestScript.h"
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

////////////////////////////////////////////////////////////
// JavaScript Engine
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScriptEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_ECHO_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineSumTest) {
  
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new Script(JavaScriptEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::JS_SUM_CODE)));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScriptEngine::LANGUAGE));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineCounterTest) {
  Error err;
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScriptEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_GETCOUNTER_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_GETCOUNTER_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_GETCOUNTER_NAME));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_SETCOUNTER_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_SETCOUNTER_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SETCOUNTER_NAME));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_INCCOUNTER_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_INCREMENTCOUNTER_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_INCCOUNTER_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runCounterMethodTest(&scriptMgr);
}

////////////////////////////////////////////////////////////
// JavaScript Function
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JavaScriptMethodTest) {

  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  BOOST_CHECK(node.stop(&err));
}

BOOST_AUTO_TEST_SUITE_END()
