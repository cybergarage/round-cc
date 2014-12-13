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

BOOST_AUTO_TEST_CASE(NodeResponseNewTest) {
  NodeResponse *res = new NodeResponse();
  BOOST_CHECK(res);
  delete res;
}

BOOST_AUTO_TEST_SUITE_END()
