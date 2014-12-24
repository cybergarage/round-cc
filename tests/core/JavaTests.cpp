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
#include <round/core/impl/Java.h>

#include "TestScript.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

BOOST_AUTO_TEST_CASE(JavaEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new JavaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_ECHO_CODE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  

  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(Test::SCRIPT_ECHO_NAME, &scriptMgr);
}

BOOST_AUTO_TEST_SUITE_END()
