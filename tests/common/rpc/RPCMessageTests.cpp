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

#include <iostream>
#include <round/common/RPC.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(RPCMessageMethodTest) {
  RPC::JSON::Message rpcMsg;
  
  const std::string TEST_VER= RPC::JSON::VERSION;
  std::string ver;
  BOOST_CHECK(!rpcMsg.getVersion(&ver));
  BOOST_CHECK(rpcMsg.setVersion(TEST_VER));
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);

  const size_t TEST_ID = 12345;
  size_t id;
  BOOST_CHECK(!rpcMsg.getId(&id));
  BOOST_CHECK(rpcMsg.setId(TEST_ID));
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);

  // Check again not to orverride.
  
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);
  
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);
}

BOOST_AUTO_TEST_CASE(RPCRequestMethodTest) {
  RPC::JSON::Request rpcMsg;
  
  const std::string TEST_VER= RPC::JSON::VERSION;
  std::string ver;
  BOOST_CHECK(!rpcMsg.getVersion(&ver));
  BOOST_CHECK(rpcMsg.setVersion(TEST_VER));
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);
  
  const std::string TEST_METHOD = "hello";
  std::string method;
  BOOST_CHECK(!rpcMsg.getMethod(&method));
  BOOST_CHECK(rpcMsg.setMethod(TEST_METHOD));
  BOOST_CHECK(rpcMsg.getMethod(&method));
  BOOST_CHECK_EQUAL(method.compare(TEST_METHOD), 0);
  
  const std::string TEST_PARAMS = "{\"value\":1}";
  std::string params;
  BOOST_CHECK(!rpcMsg.getParams(&params));
  BOOST_CHECK(rpcMsg.setParams(TEST_PARAMS));
  BOOST_CHECK(rpcMsg.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(TEST_PARAMS), 0);
  
  const size_t TEST_ID = 12345;
  size_t id;
  BOOST_CHECK(!rpcMsg.getId(&id));
  BOOST_CHECK(rpcMsg.setId(TEST_ID));
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);
  
  // Check again not to orverride.
  
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);
  
  BOOST_CHECK(rpcMsg.getMethod(&method));
  BOOST_CHECK_EQUAL(method.compare(TEST_METHOD), 0);
  
  BOOST_CHECK(rpcMsg.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(TEST_PARAMS), 0);
  
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);
}

BOOST_AUTO_TEST_CASE(RPCResponseMethodTest) {
  RPC::JSON::Response rpcMsg;
  
  const std::string TEST_VER= RPC::JSON::VERSION;
  std::string ver;
  BOOST_CHECK(!rpcMsg.getVersion(&ver));
  BOOST_CHECK(rpcMsg.setVersion(TEST_VER));
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);
  
  const size_t TEST_ID = 12345;
  size_t id;
  BOOST_CHECK(!rpcMsg.getId(&id));
  BOOST_CHECK(rpcMsg.setId(TEST_ID));
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);
  
  const std::string TEST_RESULT = "{\"value\":1}";
  std::string result;
  BOOST_CHECK(!rpcMsg.getResult(&result));
  BOOST_CHECK(rpcMsg.setResult(TEST_RESULT));
  BOOST_CHECK(rpcMsg.getResult(&result));
  BOOST_CHECK_EQUAL(result.compare(TEST_RESULT), 0);
  
  const std::string TEST_RESULT_DIR_KEY = "key01";
  const std::string TEST_RESULT_DIR_VALUE = "value01";
  std::string dirResult;
  BOOST_CHECK(!rpcMsg.getResult(TEST_RESULT_DIR_KEY, &dirResult));
  BOOST_CHECK(rpcMsg.setResult(TEST_RESULT_DIR_KEY, TEST_RESULT_DIR_VALUE));
  BOOST_CHECK(rpcMsg.getResult(TEST_RESULT_DIR_KEY, &dirResult));
  BOOST_CHECK_EQUAL(dirResult.compare(TEST_RESULT_DIR_VALUE), 0);
  
  // Check again not to orverride.
  
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(TEST_VER), 0);
  
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id, TEST_ID);
  
  BOOST_CHECK(rpcMsg.getResult(TEST_RESULT_DIR_KEY, &dirResult));
  BOOST_CHECK_EQUAL(dirResult.compare(TEST_RESULT_DIR_VALUE), 0);
}

class TestMessageParser : public JSONParser {
  
public:
  
  TestMessageParser() {
  }

  JSONDictionary *createJSONDictionary() {
    return new RPC::JSON::Request();
  }
};

BOOST_AUTO_TEST_CASE(RPCRequestTest) {
  TestMessageParser jsonParser;
  RPC::JSON::Request *req;
  std::string inputStr, jsonStr;
  
  // rpc call with positional parameters:
/* FIXME Return false
  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42, 23], \"id\": 1}";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(!req->isNotify());
*/  
  // rpc call with named parameters:

  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": {\"subtrahend\": 23, \"minuend\": 42}, \"id\": 3}";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(!req->isNotify());
  
  // a Notification:

  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5]}";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(req->isNotify());

  // rpc call with invalid JSON:

  inputStr = " {\"jsonrpc\": \"2.0\", \"method\": \"foobar, \"params\": \"bar\", \"baz]";
  BOOST_CHECK(!jsonParser.parse(inputStr));
  
  // rpc call with invalid Request object:
  
  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": 1, \"params\": \"bar\"}";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(!req->isValid());
  
  //rpc call with an empty Array:
  
  inputStr = "[]";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(!req);
  
  // rpc call with an invalid Batch (but not empty):

  inputStr = "[1]";
  BOOST_CHECK(jsonParser.parse(inputStr));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getObject());
  BOOST_CHECK(!req);
}

BOOST_AUTO_TEST_CASE(RPCErrorMethodTest) {
  RPC::JSON::Response rpcMsg;

  const std::string detailMsg = "67890";
  Error TEST_ERROR(12345, "12345", 67890, detailMsg);
  Error err;
  
  BOOST_CHECK(!rpcMsg.getError(&err));
  BOOST_CHECK(rpcMsg.setError(&TEST_ERROR));
  
  BOOST_CHECK(rpcMsg.getError(&err));
  BOOST_CHECK_EQUAL(err.getDetailCode(), TEST_ERROR.getDetailCode());
  BOOST_CHECK_EQUAL(detailMsg.compare(err.getDetailMessage()), 0);
}

BOOST_AUTO_TEST_SUITE_END()
