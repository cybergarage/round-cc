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
#include <boost/algorithm/string.hpp>

#include <round/common/JSON.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(json)

////////////////////////////////////////////////////////////
// For Dictionary in Directory
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseRpcBasicMessageTest01) {
  const char *testString = "{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"_set_method\",\"params\":{\"code\":\"function echo(params) {return params;}\",\"language\":\"js\",\"name\":\"echo\"}}";
  
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  
  JSONObject *rootObj = jsonParser.getRootObject();
  BOOST_CHECK(rootObj);
  BOOST_CHECK(rootObj->isDictionary());
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(rootObj);
  BOOST_CHECK(jsonDict);
  
  std::string jsonStr;
  JSONObject *jsonObj;
  
  BOOST_CHECK(jsonDict->get("id", &jsonStr));
  BOOST_CHECK_EQUAL(jsonStr.compare("1"), 0);
  
  BOOST_CHECK(jsonDict->get("jsonrpc", &jsonStr));
  BOOST_CHECK_EQUAL(jsonStr.compare("2.0"), 0);
  
  BOOST_CHECK(jsonDict->get("method", &jsonStr));
  BOOST_CHECK_EQUAL(jsonStr.compare("_set_method"), 0);
  
  BOOST_CHECK(jsonDict->get("params", &jsonObj));
}

////////////////////////////////////////////////////////////
// For Array
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONRPCGetClusterTest) {
  const std::string testString = " {\"id\":\"6\",\"jsonrpc\":\"2.0\",\"result\":{\"cluster\":{\"nodes\":[\"{\"cluster\":\"round\",\"hash\":\"D0F02577D7855CA1C3EE6E3A6DC64D2A26648B81\",\"ip\":\"172.20.10.2\",\"port\":\"12072\"}\"]}},\"ts\":\"4\"}";

  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  
  JSONObject *rootObj = jsonParser.getRootObject();
  BOOST_CHECK(rootObj);
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(rootObj);
  BOOST_CHECK(jsonDict);
  
  std::string jsonStr;
  JSONObject *jsonObj;
  
  BOOST_CHECK(jsonDict->get("id", &jsonStr));
  BOOST_CHECK_EQUAL(jsonStr.compare("6"), 0);
  
  BOOST_CHECK(jsonDict->get("jsonrpc", &jsonStr));
  BOOST_CHECK_EQUAL(jsonStr.compare("2.0"), 0);
  
  BOOST_CHECK(jsonDict->get("result", &jsonObj));
  
  JSONDictionary *resultDir = dynamic_cast<JSONDictionary *>(jsonObj);
  BOOST_CHECK(resultDir);
  
}

BOOST_AUTO_TEST_SUITE_END()
