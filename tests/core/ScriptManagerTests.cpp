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
#include <round/script/JavaScript.h>

#include "TestScript.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

BOOST_AUTO_TEST_CASE(ScriptManagerSetTest) {
  const std::string scriptLang = JavaScriptEngine::LANGUAGE;
  const std::string scriptMethod = "echo";
  const std::string scriptCode = Test::JS_ECHO_CODE;
  const std::string scriptInvalidCode = Test::JS_INVALID_FUNCTION;
  const std::string scriptParam = "\"hello\"";

  ScriptManager scriptMgr;
  std::string scriptResult;
  Error err;
  
  // No Script Engine
  
  BOOST_CHECK(!scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, Script::ENCODING_NONE, &err));
  BOOST_CHECK(err.getDetailCode() == RPC::JSON::ErrorCodeScriptEngineNotFound);

  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));
  
  // Set Script Engine
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));

  // No Script
  
  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));
  BOOST_CHECK(err.getDetailCode() == RPC::JSON::ErrorCodeMethodNotFound);
  
  // Set Script
  
  BOOST_CHECK(!scriptMgr.setScript(scriptMethod, scriptLang, scriptInvalidCode, Script::ENCODING_NONE, &err));
  BOOST_CHECK(err.getDetailCode() == RPC::JSON::ErrorCodeScriptCompileError);
  
  BOOST_CHECK(scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, Script::ENCODING_NONE, &err));

  BOOST_CHECK(scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));
  BOOST_CHECK_EQUAL(scriptParam, scriptResult);

  // Overide Script
  
  BOOST_CHECK(scriptMgr.setScript(scriptMethod, scriptLang, scriptCode, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));
  BOOST_CHECK_EQUAL(scriptParam, scriptResult);

  // Remove Script
  
  BOOST_CHECK(scriptMgr.setScript(scriptMethod, scriptLang, "", Script::ENCODING_NONE, &err));
  
  BOOST_CHECK(!scriptMgr.run(scriptMethod, scriptParam, &scriptResult, &err));
  BOOST_CHECK(err.getDetailCode() == RPC::JSON::ErrorCodeMethodNotFound);
}

BOOST_AUTO_TEST_SUITE_END()

