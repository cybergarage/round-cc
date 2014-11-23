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

#include <round/core/impl/JavaScript.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(JavaScriptTest) {
  JavaScript script;
  BOOST_CHECK(script.run());
}
