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
  const std::string TEST_NAME = "aname";
  const std::string TEST_OBJECT = "asource";
  const std::string TEST_DEFAULTS = "adefaults";
  
  Alias alias;
  std::string name, object, params;
  
  // initialize node
  
  BOOST_CHECK_EQUAL(alias.isValid(), false);
  BOOST_CHECK_EQUAL(alias.getName(&name), false);
  BOOST_CHECK_EQUAL(alias.getObject(&object), false);
  BOOST_CHECK_EQUAL(alias.getDefaults(&params), false);

  // name

  BOOST_CHECK_EQUAL(alias.setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(alias.isValid(), false);
  BOOST_CHECK_EQUAL(alias.getName(&name), true);
  BOOST_CHECK_EQUAL(name.compare(TEST_NAME), 0);

  // object
  
  BOOST_CHECK_EQUAL(alias.setObject(TEST_OBJECT), true);
  BOOST_CHECK_EQUAL(alias.isValid(), true);
  BOOST_CHECK_EQUAL(alias.getObject(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_OBJECT), 0);

  // default params
  
  BOOST_CHECK_EQUAL(alias.setDefaults(TEST_DEFAULTS), true);
  BOOST_CHECK_EQUAL(alias.isValid(), true);
  BOOST_CHECK_EQUAL(alias.getDefaults(&params), true);
  BOOST_CHECK_EQUAL(params.compare(TEST_DEFAULTS), 0);
}

BOOST_AUTO_TEST_CASE(AliasMapTest) {
  const std::string TEST_NAME = "tname";
  const std::string TEST_OBJECT = "tsource";
  
  AliasMap aliasMap;
  Alias *alias;
  
  // initialize node
  
  BOOST_CHECK_EQUAL(aliasMap.size(), 0);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), false);
  
  // addAlias

  alias = new Alias();
  BOOST_CHECK_EQUAL(alias->setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(alias->setObject(TEST_OBJECT), true);
  
  BOOST_CHECK_EQUAL(aliasMap.addAlias(alias), true);
  BOOST_CHECK_EQUAL(aliasMap.size(), 1);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), true);
  
  BOOST_CHECK_EQUAL(aliasMap.addAlias(alias), false);
  BOOST_CHECK_EQUAL(aliasMap.size(), 1);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), true);

  // setAlias
  
  alias = new Alias();
  BOOST_CHECK_EQUAL(alias->setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(alias->setObject(TEST_NAME), true);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), true);
  
  BOOST_CHECK_EQUAL(aliasMap.setAlias(alias), true);
  BOOST_CHECK_EQUAL(aliasMap.size(), 1);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), true);

  // findAlias
  
  Alias *foundAlias = aliasMap.findAlias(TEST_NAME);
  BOOST_CHECK(foundAlias);
  BOOST_CHECK_EQUAL(foundAlias->equals(alias), true);
  
  // removeAlias
  
  BOOST_CHECK_EQUAL(aliasMap.removeAliasByName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(aliasMap.size(), 0);
  BOOST_CHECK_EQUAL(aliasMap.hasAlias(TEST_NAME), false);
}

BOOST_AUTO_TEST_SUITE_END()
