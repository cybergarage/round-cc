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

#include <stdio.h>
#include <time.h>

#include <round/common/RPC.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundRPCMessageMethodTest) {
  RPC::JSON::Message rpcMsg;
  
  std::string ver;
  BOOST_CHECK(rpcMsg.getVersion(&ver));
  BOOST_CHECK_EQUAL(ver.compare(RPC::JSON::Message::VERSION), 0);

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

  const std::string TEST_ID = "12345";
  std::string id;
  BOOST_CHECK(!rpcMsg.getId(&id));
  BOOST_CHECK(rpcMsg.setId(TEST_ID));
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id.compare(TEST_ID), 0);

  const std::string TEST_RESULT = "{\"value\":1}";
  std::string result;
  BOOST_CHECK(!rpcMsg.getResult(&params));
  BOOST_CHECK(rpcMsg.setResult(TEST_RESULT));
  BOOST_CHECK(rpcMsg.getParams(&result));
  BOOST_CHECK_EQUAL(result.compare(TEST_RESULT), 0);
  
  Error TEST_ERROR(12345, "12345");
  Error err;
  BOOST_CHECK(!rpcMsg.getError(&err));
  BOOST_CHECK(rpcMsg.setError(TEST_ERROR));
  BOOST_CHECK(rpcMsg.getError(&err));
  BOOST_CHECK(err.equals(TEST_ERROR));
  
  // Check again not to orverride.
  
  BOOST_CHECK_EQUAL(ver.compare(RPC::JSON::Message::VERSION), 0);
  
  BOOST_CHECK(rpcMsg.getMethod(&method));
  BOOST_CHECK_EQUAL(method.compare(TEST_METHOD), 0);
  
  BOOST_CHECK(rpcMsg.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(TEST_PARAMS), 0);
  
  BOOST_CHECK(rpcMsg.getId(&id));
  BOOST_CHECK_EQUAL(id.compare(TEST_ID), 0);
  
  BOOST_CHECK(rpcMsg.getParams(&result));
  BOOST_CHECK_EQUAL(result.compare(TEST_RESULT), 0);
  
  BOOST_CHECK(rpcMsg.getParams(&result));
  BOOST_CHECK_EQUAL(result.compare(TEST_RESULT), 0);

}
