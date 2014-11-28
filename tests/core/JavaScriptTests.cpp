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

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(JavaScriptEngineEchoTest) {
  
  const std::string ECHO_NAME = "echo";
  const std::string ECHO_CONTEXT =
    "function echo(params) {" \
    "  return params;" \
    "}";

  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setScript(new JavaScript(ECHO_NAME, ECHO_CONTEXT)));
  BOOST_CHECK(scriptMgr.hasScript(ECHO_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaScriptEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaScript::LANGUAGE));
  
  std::vector<std::string> echoParams;
  
  echoParams.push_back("");
  echoParams.push_back("1");
  echoParams.push_back("\"1\"");
  echoParams.push_back("\"Hello\"");
  
  echoParams.push_back("[]");
  
  echoParams.push_back("[0]");
  echoParams.push_back("[0,1]");
  echoParams.push_back("[0,1,2]");
  
  echoParams.push_back("[\"0\"]");
  echoParams.push_back("[\"0\",\"1\"]");
  echoParams.push_back("[\"0\",\"1\",\"2\"]");
  
  echoParams.push_back("{}");
  
  echoParams.push_back("{\"key\":0}");
  echoParams.push_back("{\"key0\":0,\"key1\":1}");
  echoParams.push_back("{\"key0\":0,\"key1\":1,\"key2\":2}");
  
  echoParams.push_back("{\"key0\":\"value0\"}");
  echoParams.push_back("{\"key0\":\"value0\",\"key1\":\"value1\"}");
  echoParams.push_back("{\"key0\":\"value0\",\"key1\":\"value1\",\"key2\":\"value2\"}");

  ScriptResults results;
  Error error;
  for (std::vector<std::string>::iterator echoParamIt = echoParams.begin(); echoParamIt != echoParams.end(); echoParamIt++) {
    std::string &echoParam = *echoParamIt;
    BOOST_CHECK(scriptMgr.run(ECHO_NAME, echoParam, &results, &error));
    BOOST_CHECK_EQUAL(echoParam.compare(results), 0);
  }
}
