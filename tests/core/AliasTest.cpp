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

#include <round/core/Alias.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(alias)

BOOST_AUTO_TEST_CASE(AliasTest) {
  const std::string TEST_NAME = "rname";
  const std::string TEST_SRC_METHOD = "smethod";
  const std::string TEST_SRC_NODE = "snode";
  const std::string TEST_SRC_CLUSTER = "scluster";
  
  const std::string TEST_DEST_METHOD = "dmethod";
  const std::string TEST_DEST_NODE = "dnode";
  const std::string TEST_DEST_CLUSTER = "dcluster";
  
  Alias alias;
  std::string name, object;
  
  // initialize node
  
  BOOST_CHECK_EQUAL(alias.isValid(), false);
  BOOST_CHECK_EQUAL(alias.getName(&name), false);

  // "name"

  BOOST_CHECK_EQUAL(alias.setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(alias.isValid(), true);
  BOOST_CHECK_EQUAL(alias.getName(&name), true);
}

BOOST_AUTO_TEST_SUITE_END()

