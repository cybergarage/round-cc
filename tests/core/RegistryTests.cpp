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

#include <sstream>
#include <round/core/Registry.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(registry)

BOOST_AUTO_TEST_CASE(RQLRregistryBasicMethodTest) {

  std::string val;
  time_t ts;
  std::stringstream ss;
  std::string sval;
  time_t tval;
  
  Registry reg;
  
  BOOST_CHECK_EQUAL(reg.getKey(&sval), false);
  BOOST_CHECK_EQUAL(reg.getValue(&sval), false);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), false);
  BOOST_CHECK_EQUAL(reg.getLogicalTimestamp(tval), false);

  time(&ts); ss << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setValue(val), true);
  BOOST_CHECK_EQUAL(reg.getValue(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts); ss << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setKey(val), true);
  BOOST_CHECK_EQUAL(reg.getKey(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts);
  BOOST_CHECK_EQUAL(reg.setTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);

  time(&ts);
  BOOST_CHECK_EQUAL(reg.setTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);
}

BOOST_AUTO_TEST_SUITE_END()
