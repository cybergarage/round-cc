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

#define JS_JOB_SCRIPT_BUF_SIZE 1024

#define JS_TEST_JOB_HELLO "hello"
#define JS_TEST_JOB_HELLO_SCRIPT \
  "\"" JS_TEST_JOB_HELLO "\";"

BOOST_AUTO_TEST_CASE(JavaScriptHelloTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_HELLO_SCRIPT, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare(JS_TEST_JOB_HELLO), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_GETNETWORKSTATE \
  "var result = " ROUNDCC_SYSTEM_METHOD_GET_NETWORK_STATE "();\n" \
  "//print(result);\n" \
  "var jsonResult = JSON.parse(result);\n" \
  "jsonResult.clusters.length;\n"

BOOST_AUTO_TEST_CASE(JavaScriptGetNetworkStateMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_GETNETWORKSTATE, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("1"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_GETCLUSTERSTATE \
  "var result = " ROUNDCC_SYSTEM_METHOD_GET_CLUSTER_STATE "();\n" \
  "//print(result);\n" \
  "var jsonResult = JSON.parse(result);\n" \
  "jsonResult.cluster.nodes.length;\n"

BOOST_AUTO_TEST_CASE(JavaScriptGetClusterStateMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_GETCLUSTERSTATE, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("1"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_GETNODESTATE \
"var result = " ROUNDCC_SYSTEM_METHOD_GET_NODE_STATE "();\n" \
"//print(result);\n" \
"var jsonResult = JSON.parse(result);\n" \
"jsonResult.hash;\n"

BOOST_AUTO_TEST_CASE(JavaScriptGetNodeMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_GETNODESTATE, Round::Script::ENCODING_NONE, &result, &err));

  std::string nodeHash;
  node.getHashCode(&nodeHash);
  
  BOOST_CHECK_EQUAL(result.compare(nodeHash), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_SETREGISTORY \
  "var key = \"%s\";\n" \
  "var val = \"%s\";\n" \
  ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val);\n" \
  "var reg = " ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "(key);\n" \
  "//print(reg);\n" \
  "var jsonReg = JSON.parse(reg);\n" \
  "if (val != jsonReg.value) {\n" \
  "  print(jsonReg.value);\n" \
  "}\n" \
  "(val == jsonReg.value);\n"

BOOST_AUTO_TEST_CASE(JavaScriptRegistryBasicMethodTest) {

  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[JS_JOB_SCRIPT_BUF_SIZE+1];
  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             JS_JOB_SCRIPT_BUF_SIZE,
             JS_TEST_JOB_SETREGISTORY,
             key.c_str(),
             val.c_str());
  
    std::string result;
    BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare("true"), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_GETREGISTORY_ERROR \
"var key = \"error_key\";\n" \
"var reg = " ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "(key);\n" \
"reg;\n"

BOOST_AUTO_TEST_CASE(JavaScriptRegistryErrorMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_GETREGISTORY_ERROR, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("false"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_REMOVEREGISTORY \
"var key = \"%s\";\n" \
"var val = \"%s\";\n" \
ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val);\n" \
"var result = " ROUNDCC_SYSTEM_METHOD_REMOVE_REGISTRY "(key);\n" \
"//print(result);\n" \
"result;\n"

BOOST_AUTO_TEST_CASE(JavaScriptRegistryRemoveMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[JS_JOB_SCRIPT_BUF_SIZE+1];
  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             JS_JOB_SCRIPT_BUF_SIZE,
             JS_TEST_JOB_REMOVEREGISTORY,
             key.c_str(),
             val.c_str());
    
    std::string result;
    BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare("true"), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_POSTMETHOD \
  "var key = \"%s\";\n" \
  "var val = \"%s\";\n" \
  ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val);\n" \
  "var result = " ROUNDCC_SCRIPT_POST_METHOD "('" ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "', '{\"key\": \"%s\"}');\n" \
  "var jsonReg = JSON.parse(result);\n" \
  "if (val != jsonReg.value) {\n" \
  "  print(result);\n" \
  "}\n" \
  "(val == jsonReg.value);\n"

BOOST_AUTO_TEST_CASE(JavaScriptPostMethodTest) {
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[JS_JOB_SCRIPT_BUF_SIZE+1];

  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             JS_JOB_SCRIPT_BUF_SIZE,
             JS_TEST_JOB_POSTMETHOD,
             key.c_str(),
             val.c_str(),
             key.c_str());
    
    std::string result;
    BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare("true"), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

#define JS_TEST_JOB_POSTMETHOD_ERROR \
"var result = " ROUNDCC_SCRIPT_POST_METHOD "('error_method', '');\n" \
"result;\n"

BOOST_AUTO_TEST_CASE(JavaScriptPostMethodErrorTest) {
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(JavaScriptEngine::LANGUAGE, JS_TEST_JOB_POSTMETHOD_ERROR, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("false"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

BOOST_AUTO_TEST_SUITE_END()
