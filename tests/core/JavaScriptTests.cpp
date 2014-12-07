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

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest) {
  
  const std::string JS_NAME = "echo";
  const std::string JS_SCRIPT = Round::Test::JS_ECHO;
  
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setScript(new JavaScript(JS_NAME, JS_SCRIPT)));
  BOOST_CHECK(scriptMgr.hasScript(JS_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScript::LANGUAGE));
  
  std::vector<std::string> params;
  
  params.push_back("");
  params.push_back("1");
  params.push_back("\"1\"");
  params.push_back("\"Hello\"");
  
  params.push_back("[]");
  
  params.push_back("[0]");
  params.push_back("[0,1]");
  params.push_back("[0,1,2]");
  
  params.push_back("[\"0\"]");
  params.push_back("[\"0\",\"1\"]");
  params.push_back("[\"0\",\"1\",\"2\"]");
  
  params.push_back("{}");
  
  params.push_back("{\"key\":0}");
  params.push_back("{\"key0\":0,\"key1\":1}");
  params.push_back("{\"key0\":0,\"key1\":1,\"key2\":2}");
  
  params.push_back("{\"key0\":\"value0\"}");
  params.push_back("{\"key0\":\"value0\",\"key1\":\"value1\"}");
  params.push_back("{\"key0\":\"value0\",\"key1\":\"value1\",\"key2\":\"value2\"}");

  ScriptResults results;
  Error error;
  for (std::vector<std::string>::iterator echoParamIt = params.begin(); echoParamIt != params.end(); echoParamIt++) {
    std::string &echoParam = *echoParamIt;
    BOOST_CHECK(scriptMgr.run(JS_NAME, echoParam, &results, &error));
    BOOST_CHECK_EQUAL(echoParam.compare(results), 0);
  }
}

BOOST_AUTO_TEST_CASE(JavaScriptEngineTest) {
  
  const std::string JS_NAME = "sum";
  const std::string JS_SCRIPT = Round::Test::JS_SUM;
  
  std::cout << JS_SCRIPT << std::endl;

  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new JavaScript(JS_NAME, JS_SCRIPT)));
  BOOST_CHECK(scriptMgr.hasScript(JS_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScript::LANGUAGE));
  
  std::vector<std::string> params;
  std::vector<std::string> results;

  params.push_back("[1]");
  results.push_back("1");

  params.push_back("[1,2]");
  results.push_back("3");
  
  params.push_back("[1,2,3]");
  results.push_back("6");
  
  params.push_back("[0,1,2,3,4,5,6,7,8,9]");
  results.push_back("45");
  
  params.push_back("[10,20,30]");
  results.push_back("60");
  
  params.push_back("[10,20]");
  results.push_back("30");
  
  params.push_back("[10,20,30]");
  results.push_back("60");
  
  params.push_back("[0,10,20,30,40,50,60,70,80,90]");
  results.push_back("450");
  
  size_t nParams = params.size();
  for (size_t n = 0; n < nParams; n++) {
    ScriptResults result;
    Error error;
    BOOST_CHECK(scriptMgr.run(JS_NAME, params[n], &result, &error));
    std::cout << result << std::endl;
    BOOST_CHECK_EQUAL(result.compare(results[n]), 0);
  }
}
