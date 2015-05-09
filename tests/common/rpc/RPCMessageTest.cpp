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

#include <iostream>
#include <round/common/RPC.h>
#include <round/common/digest/SHA.h>
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(RPCMessageMethodTest) {
  RPC::JSON::Message rpcMsg;
  
  const std::string TEST_VER= RPC::JSON::VER;
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
  
  const std::string TEST_VER= RPC::JSON::VER;
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
  BOOST_CHECK(!rpcMsg.hasParams());
  BOOST_CHECK(!rpcMsg.getParams(&params));
  BOOST_CHECK(rpcMsg.setParams(TEST_PARAMS));
  BOOST_CHECK(rpcMsg.hasParams());
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
  
  const std::string TEST_VER= RPC::JSON::VER;
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

BOOST_AUTO_TEST_CASE(RPCRequestExtentionMethodTest) {
  RPC::JSON::Message rpcMsg;
  
  // timestamp
  
  clock_t ts;
  
  BOOST_CHECK(!rpcMsg.hasTimestamp());
  BOOST_CHECK(!rpcMsg.getTimestamp(&ts));
  
  rpcMsg.setTimestamp(std::numeric_limits<clock_t>::min());
  BOOST_CHECK(rpcMsg.hasTimestamp());
  BOOST_CHECK(rpcMsg.getTimestamp(&ts));
  BOOST_CHECK_EQUAL(ts, std::numeric_limits<clock_t>::min());
  
  rpcMsg.setTimestamp(std::numeric_limits<clock_t>::max());
  BOOST_CHECK(rpcMsg.hasTimestamp());
  BOOST_CHECK(rpcMsg.getTimestamp(&ts));
  BOOST_CHECK_EQUAL(ts, std::numeric_limits<clock_t>::max());

  // type
  
  const std::string TEST_TYPE = "paxos";
  std::string type;
  
  BOOST_CHECK(!rpcMsg.hasType());
  BOOST_CHECK(!rpcMsg.getType(&type));
  
  BOOST_CHECK(rpcMsg.setType(TEST_TYPE));
  BOOST_CHECK(rpcMsg.hasType());
  BOOST_CHECK(rpcMsg.getType(&type));
  BOOST_CHECK_EQUAL(TEST_TYPE.compare(type), 0);
  
  // digest
  
  const std::string TEST_DIGEST = "abcdefghijklmnopqrstuvwxyz";
  std::string digest;
  
  BOOST_CHECK(!rpcMsg.hasDigest());
  BOOST_CHECK(!rpcMsg.getDigest(&digest));
  
  BOOST_CHECK(rpcMsg.setDigest(TEST_DIGEST));
  BOOST_CHECK(rpcMsg.hasDigest());
  BOOST_CHECK(rpcMsg.getDigest(&digest));
  BOOST_CHECK_EQUAL(TEST_DIGEST.compare(digest), 0);

  // cond
  
  const std::string TEST_COND = "paramOut";
  std::string cond;
  
  BOOST_CHECK(!rpcMsg.hasCond());
  BOOST_CHECK(!rpcMsg.getCond(&cond));
  
  BOOST_CHECK(rpcMsg.setCond(TEST_COND));
  BOOST_CHECK(rpcMsg.hasCond());
  BOOST_CHECK(rpcMsg.getCond(&cond));
  BOOST_CHECK_EQUAL(TEST_COND.compare(cond), 0);
  
  // dest
  
  std::string dest;
  
  BOOST_CHECK(!rpcMsg.hasDest());
  BOOST_CHECK(!rpcMsg.getDest(&dest));
  BOOST_CHECK(rpcMsg.isDestValid());
  BOOST_CHECK(rpcMsg.isDestOne());
  BOOST_CHECK(!rpcMsg.isDestHash());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());
  
  const std::string TEST_DEST = "0123456789";
  BOOST_CHECK(rpcMsg.setDest(TEST_DEST));
  BOOST_CHECK(rpcMsg.hasDest());
  BOOST_CHECK(rpcMsg.getDest(&dest));
  BOOST_CHECK_EQUAL(TEST_DEST.compare(dest), 0);
  BOOST_CHECK(!rpcMsg.isDestValid());
  BOOST_CHECK(!rpcMsg.isDestOne());
  BOOST_CHECK(!rpcMsg.isDestHash());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());
  
  BOOST_CHECK(rpcMsg.setDest(RPC::JSON::Message::DEST_ALL));
  BOOST_CHECK(rpcMsg.isDestValid());
  BOOST_CHECK(rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());
  BOOST_CHECK(!rpcMsg.isDestHash());
  BOOST_CHECK(!rpcMsg.isDestOne());

  BOOST_CHECK(rpcMsg.setDest(RPC::JSON::Message::DEST_ANY));
  BOOST_CHECK(rpcMsg.isDestValid());
  BOOST_CHECK(rpcMsg.isDestAny());
  BOOST_CHECK(rpcMsg.isDestOne());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestHash());
  
  std::string TEST_GOOD_HASH;
  SHA256::Hash("123456789", &TEST_GOOD_HASH);
  BOOST_CHECK(rpcMsg.setDest(TEST_GOOD_HASH));
  BOOST_CHECK(rpcMsg.isDestValid());
  BOOST_CHECK(rpcMsg.isDestHash());
  BOOST_CHECK(rpcMsg.isDestOne());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());

  TestLocalNode node;
  std::string nodeHash;
  BOOST_CHECK(rpcMsg.setDest(&node));
  BOOST_CHECK(rpcMsg.hasDest());
  BOOST_CHECK(rpcMsg.getDest(&dest));
  BOOST_CHECK(node.getHashCode(&nodeHash));
  BOOST_CHECK_EQUAL(nodeHash.compare(dest), 0);
  BOOST_CHECK(rpcMsg.isDestValid());
  BOOST_CHECK(rpcMsg.isDestHash());
  BOOST_CHECK(rpcMsg.isDestOne());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());
  
  const std::string TEST_BAD_HASH = "a";
  BOOST_CHECK(rpcMsg.setDest(TEST_BAD_HASH));
  BOOST_CHECK(!rpcMsg.isDestValid());
  BOOST_CHECK(!rpcMsg.isDestHash());
  BOOST_CHECK(!rpcMsg.isDestAll());
  BOOST_CHECK(!rpcMsg.isDestAny());
  BOOST_CHECK(!rpcMsg.isDestOne());
}

BOOST_AUTO_TEST_CASE(RPCRequestParserTest) {
  Error error;
  RPC::JSON::Parser jsonParser;
  RPC::JSON::Request *req;
  RPC::JSON::BatchRequest *batchReq;
  std::string inputStr, jsonStr;
  
  // rpc call with positional parameters:
  
  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42, 23], \"id\": 1}";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(!req->isNotify());
  
  // rpc call with named parameters:

  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": {\"subtrahend\": 23, \"minuend\": 42}, \"id\": 3}";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(!req->isNotify());
  
  // a Notification:

  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5]}";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(req->isValid());
  BOOST_CHECK(req->isNotify());

  // rpc call with invalid JSON:

  inputStr = " {\"jsonrpc\": \"2.0\", \"method\": \"foobar, \"params\": \"bar\", \"baz]";
  BOOST_CHECK(!jsonParser.parse(inputStr, &error));
  
  // rpc call with invalid Request object:
  
  inputStr = "{\"jsonrpc\": \"2.0\", \"method\": 1, \"params\": \"bar\"}";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(!req->isValid());
  
  // rpc call Batch, invalid JSON:
  
  inputStr = "[{\"jsonrpc\": \"2.0\", \"method\": \"sum\", \"params\": [1,2,4], \"id\": \"1\"},{\"jsonrpc\": \"2.0\", \"method\"]";
  BOOST_CHECK(!jsonParser.parse(inputStr, &error));
  
  // rpc call with an empty Array:
  
  inputStr = "[]";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(!req);
  
  // rpc call with an invalid Batch (but not empty):

  inputStr = "[1]";
  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  req = dynamic_cast<RPC::JSON::Request *>(jsonParser.getRootObject());
  BOOST_CHECK(!req);

  // rpc call Batch:
  inputStr =
    "[" \
      "{\"jsonrpc\": \"2.0\", \"method\": \"sum\", \"params\": [1,2,4], \"id\": \"1\"}," \
      "{\"jsonrpc\": \"2.0\", \"method\": \"notify_hello\", \"params\": [7]}," \
      "{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42,23], \"id\": \"2\"}," \
      "{\"foo\": \"boo\"}," \
      "{\"jsonrpc\": \"2.0\", \"method\": \"foo.get\", \"params\": {\"name\": \"myself\"}, \"id\": \"5\"}," \
      "{\"jsonrpc\": \"2.0\", \"method\": \"get_data\", \"id\": \"9\"}" \
      "]";

  BOOST_CHECK(jsonParser.parse(inputStr, &error));
  batchReq = dynamic_cast<RPC::JSON::BatchRequest *>(jsonParser.getRootObject());
  BOOST_CHECK(batchReq);
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

BOOST_AUTO_TEST_CASE(RPCBatchModeTest) {
  RPC::JSON::Response rpcMsg;
  
  const std::string detailMsg = "67890";
  Error TEST_ERROR(12345, "12345", 67890, detailMsg);
  Error err;
  
  BOOST_CHECK(!rpcMsg.isBatchResult());
  
  BOOST_CHECK(rpcMsg.setResult(new JSONArray()));
  BOOST_CHECK(rpcMsg.isBatchResult());
}

BOOST_AUTO_TEST_SUITE_END()
