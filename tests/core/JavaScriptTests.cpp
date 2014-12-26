/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <vector>
#include <round/core/impl/JavaScript.h>

#include "TestScript.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScriptEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, JavaScriptEngine::LANGUAGE, Round::Test::JS_ECHO_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(Test::SCRIPT_ECHO_NAME, &scriptMgr);
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineTest) {
  
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new Script(JavaScriptEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::JS_SUM_CODE)));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScriptEngine::LANGUAGE));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(Test::SCRIPT_SUM_NAME, &scriptMgr);
}

BOOST_AUTO_TEST_SUITE_END()

