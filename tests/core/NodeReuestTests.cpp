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
  NodeRequestParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}"));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isDictionary());
  NodeRequest *nodeReq = static_cast<NodeRequest *>(jsonParser.getObject());
  BOOST_CHECK(nodeReq);
}

BOOST_AUTO_TEST_SUITE_END()

