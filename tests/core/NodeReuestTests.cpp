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

#include <round/core/NodeMessage.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(NodeRequestConstructorTest) {
  const std::string TEST_METHOD = "hello";
  
  NodeRequest nodeReq(TEST_METHOD);
  BOOST_CHECK(nodeReq.hasMethod());
  BOOST_CHECK(nodeReq.isMethod(TEST_METHOD));

  BOOST_CHECK(!nodeReq.isMethod(""));
}

BOOST_AUTO_TEST_CASE(NodeRequestParserTest) {
  Error error;
  NodeRequestParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  NodeRequest *nodeReq = static_cast<NodeRequest *>(jsonParser.getRootObject());
  BOOST_CHECK(nodeReq);
}

BOOST_AUTO_TEST_CASE(NodeRequestOptionTest) {
  NodeRequestOption nodeReqOpt;
  
  BOOST_CHECK_EQUAL(nodeReqOpt.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReqOpt.isAsync(), false);

  BOOST_CHECK(nodeReqOpt.setSync(false));
  BOOST_CHECK_EQUAL(nodeReqOpt.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReqOpt.isAsync(), true);

  BOOST_CHECK(nodeReqOpt.setSync(true));
  BOOST_CHECK_EQUAL(nodeReqOpt.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReqOpt.isAsync(), false);

  BOOST_CHECK(nodeReqOpt.setAsync(true));
  BOOST_CHECK_EQUAL(nodeReqOpt.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReqOpt.isAsync(), true);
  
  BOOST_CHECK(nodeReqOpt.setAsync(false));
  BOOST_CHECK_EQUAL(nodeReqOpt.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReqOpt.isAsync(), false);
}

BOOST_AUTO_TEST_SUITE_END()

