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
#include "TestNode.h"

using namespace std;
using namespace Round;

#if defined(ROUND_SUPPORT_LUA)

BOOST_AUTO_TEST_SUITE(script)

////////////////////////////////////////////////////////////
// Lua Engine
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(LuaEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, LuaEngine::LANGUAGE, Round::Test::LUA_ECHO_CODE, Script::ENCODING_NONE, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(LuaEngineSumTest) {
  
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setScript(new Script(LuaEngine::LANGUAGE, Test::SCRIPT_SUM_NAME, Test::LUA_SUM_CODE)));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  BOOST_CHECK(scriptMgr.setEngine(new LuaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(LuaEngine::LANGUAGE));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(&scriptMgr);
}

////////////////////////////////////////////////////////////
// Lua Function
////////////////////////////////////////////////////////////

#define LUA_JOB_SCRIPT_BUF_SIZE 1024

#define LUA_TEST_JOB_HELLO "hello"
#define LUA_TEST_JOB_HELLO_SCRIPT \
  "return \"" LUA_TEST_JOB_HELLO "\""
   
BOOST_AUTO_TEST_CASE(LuaHelloTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, LUA_TEST_JOB_HELLO_SCRIPT, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare(LUA_TEST_JOB_HELLO), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_GETNETWORKSTATE \
  "json = require(\"json\") -- JSON4Lua\n" \
  "result = " ROUNDCC_SYSTEM_METHOD_GET_NETWORK_STATE "()\n" \
  "-- print(result)\n" \
  "jsonResult = json.decode(result)" \
  "return #jsonResult[\"clusters\"]\n"

BOOST_AUTO_TEST_CASE(LuaGetNetworkStateMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, LUA_TEST_JOB_GETNETWORKSTATE, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("1"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_GETCLUSTERSTATE \
  "json = require(\"json\") -- JSON4Lua\n" \
  "result = " ROUNDCC_SYSTEM_METHOD_GET_CLUSTER_STATE "()\n" \
  "-- print(result)\n" \
  "jsonResult = json.decode(result)" \
  "return #jsonResult[\"cluster\"][\"nodes\"]\n"

BOOST_AUTO_TEST_CASE(LuaGetClusterStateMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, LUA_TEST_JOB_GETCLUSTERSTATE, Round::Script::ENCODING_NONE, &result, &err));
  BOOST_CHECK_EQUAL(result.compare("1"), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_GETNODESTATE \
  "json = require(\"json\") -- JSON4Lua\n" \
  "result = " ROUNDCC_SYSTEM_METHOD_GET_NODE_STATE "()\n" \
  "-- print(result)\n" \
  "jsonResult = json.decode(result)\n" \
  "return jsonResult[\"hash\"]\n"

BOOST_AUTO_TEST_CASE(LuaGetNodeMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  std::string result;
  BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, LUA_TEST_JOB_GETNODESTATE, Round::Script::ENCODING_NONE, &result, &err));
  
  std::string nodeHash;
  node.getHashCode(&nodeHash);
  
  BOOST_CHECK_EQUAL(result.compare(nodeHash), 0);
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_SETREGISTORY \
  "json = require(\"json\") -- JSON4Lua\n" \
  "key = \"%s\"\n" \
  "val = \"%s\"\n" \
  ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val)\n" \
  "ok, result = " ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "(key)\n" \
  "jsonResult = json.decode(result)\n" \
  "regVal = jsonResult[\"value\"]\n" \
  "return regVal\n"

BOOST_AUTO_TEST_CASE(LuaRegistryBasicMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[LUA_JOB_SCRIPT_BUF_SIZE+1];
  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             LUA_JOB_SCRIPT_BUF_SIZE,
             LUA_TEST_JOB_SETREGISTORY,
             key.c_str(),
             val.c_str());
    
    std::string result;
    BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare(val), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_REMOVEREGISTORY \
  "json = require(\"json\") -- JSON4Lua\n" \
  "key = \"%s\"\n" \
  "val = \"%s\"\n" \
  ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val)\n" \
  "result = " ROUNDCC_SYSTEM_METHOD_REMOVE_REGISTRY "(key)\n" \
  "-- print(result)\n" \
  "return result\n"

BOOST_AUTO_TEST_CASE(LuaRegistryRemoveMethodTest) {
  
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[LUA_JOB_SCRIPT_BUF_SIZE+1];
  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             LUA_JOB_SCRIPT_BUF_SIZE,
             LUA_TEST_JOB_REMOVEREGISTORY,
             key.c_str(),
             val.c_str());
    
    std::string result;
    BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare("true"), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

#define LUA_TEST_JOB_POSTMETHOD \
  "json = require(\"json\") -- JSON4Lua -- JSON4Lua\n" \
  "key = \"%s\"\n" \
  "val = \"%s\"\n" \
  ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "(key, val)\n" \
  "ok, result = " ROUNDCC_SCRIPT_POST_METHOD "('" ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "', '{\"key\": \"%s\"}', '')\n" \
  "jsonResult = json.decode(result)\n" \
  "regVal = jsonResult[\"value\"]\n" \
  "return regVal\n"

#define LUA_TEST_JOB_POSTMETHOD_PARAM \
""

BOOST_AUTO_TEST_CASE(LuaPostMethodTest) {
  TestLocalNode node;
  Error err;
  
  BOOST_CHECK(node.start(&err));
  
  char script[LUA_JOB_SCRIPT_BUF_SIZE+1];
  
  for (int n=0; n<10; n++) {
    time_t ts;
    
    Registry inReg;
    
    std::stringstream ss;
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    snprintf(script,
             LUA_JOB_SCRIPT_BUF_SIZE,
             LUA_TEST_JOB_POSTMETHOD,
             key.c_str(),
             val.c_str(),
             key.c_str());
    
    std::string result;
    BOOST_CHECK(node.execJob(LuaEngine::LANGUAGE, script, Round::Script::ENCODING_NONE, &result, &err));
    BOOST_CHECK_EQUAL(result.compare(val), 0);
  }
  
  BOOST_CHECK(node.stop(&err));
}

BOOST_AUTO_TEST_SUITE_END()

#endif
