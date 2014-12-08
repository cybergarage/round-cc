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

#include <round/core/Script.h>
#include <round/core/impl/JavaScript.h>

#include "TestScript.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(ScriptManagerSetTest) {
  const std::string scriptLang = JavaScriptEngine::LANGUAGE;
  const std::string scriptMethod = "echo";
  const std::string scriptCode = Test::JS_ECHO;
  const std::string scriptInvalidCode = Test::JS_INVALID_FUNCTION;
  const std::string scriptParams = "\"hello\"";

  ScriptManager scriptMgr;
  ScriptResults scriptResult;
  Error err;
  
  // No Script Engine
  
  BOOST_CHECK(!scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, &err));
  BOOST_CHECK_EQUAL(err.getDetailCode(), ScriptManagerErrorCodeScriptEngineNotFound);

  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParams, &scriptResult, &err));
  
  // Set Script Engine
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParams, &scriptResult, &err));

  // Set Script
  
  BOOST_CHECK(!scriptMgr.setScript(scriptMethod, scriptLang, scriptInvalidCode, &err));
  BOOST_CHECK_EQUAL(err.getDetailCode(), ScriptManagerErrorCodeCompileError);
  
  BOOST_CHECK(scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, &err));

  BOOST_CHECK(scriptMgr.run(scriptMethod, scriptParams, &scriptResult, &err));
  BOOST_CHECK_EQUAL(scriptParams, scriptResult);
}
