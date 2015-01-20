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
  NodeRequest nodeReq;
  
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);

  BOOST_CHECK(nodeReq.setSync(false));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), true);

  BOOST_CHECK(nodeReq.setSync(true));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);

  BOOST_CHECK(nodeReq.setAsync(true));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), true);
  
  BOOST_CHECK(nodeReq.setAsync(false));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);
}

BOOST_AUTO_TEST_SUITE_END()

