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

#include <round/core/NodeMessage.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(NodeMessageRequestParserTest) {
  NodeMessageRequestParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}"));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isDictionary());
  NodeRequest *nodeReq = static_cast<NodeRequest *>(jsonParser.getObject());
  BOOST_CHECK(nodeReq);
}


