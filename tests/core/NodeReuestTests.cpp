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

BOOST_AUTO_TEST_CASE(NodeRequestConstructorTest) {
  const std::string TEST_METHOD = "hello";
  
  NodeRequest nodeReq(TEST_METHOD);
  BOOST_CHECK(nodeReq.hasMethod());
  BOOST_CHECK(nodeReq.isMethod(TEST_METHOD));

  BOOST_CHECK(!nodeReq.isMethod(""));
}

