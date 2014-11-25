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

#include <round/core/impl/JavaScript.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest) {
  
  const std::string ECHO_NAME = "echo";
  const std::string ECHO_CONTEXT =
    "function echo(params) {" \
    "  return params;" \
    "}";
  
  JavaScript *helloScript = new JavaScript(ECHO_NAME, ECHO_CONTEXT);
  
  JavaScriptEngine jsEngine;
  
  BOOST_CHECK(!jsEngine.hasScript(ECHO_NAME));
  jsEngine.setScript(helloScript);
  BOOST_CHECK(jsEngine.hasScript(ECHO_NAME));
  
  ScriptResults results;
  Error error;

  const std::string ECHO_PARAM_01 = "{}";
  BOOST_CHECK(jsEngine.run(ECHO_NAME, ECHO_PARAM_01, &results, &error));
  BOOST_CHECK_EQUAL(ECHO_PARAM_01.compare(results), 0);

  const std::string ECHO_PARAM_02 = "[]";
  BOOST_CHECK(jsEngine.run(ECHO_NAME, ECHO_PARAM_02, &results, &error));
  BOOST_CHECK_EQUAL(ECHO_PARAM_02.compare(results), 0);

  const std::string ECHO_PARAM_03 = "{\"key\":0}";
  BOOST_CHECK(jsEngine.run(ECHO_NAME, ECHO_PARAM_03, &results, &error));
  BOOST_CHECK_EQUAL(ECHO_PARAM_03.compare(results), 0);

  const std::string ECHO_PARAM_04 = "{\"key\":\"value\"}";
  BOOST_CHECK(jsEngine.run(ECHO_NAME, ECHO_PARAM_04, &results, &error));
  BOOST_CHECK_EQUAL(ECHO_PARAM_04.compare(results), 0);
}
