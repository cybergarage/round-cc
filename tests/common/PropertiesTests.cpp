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
#include <boost/algorithm/string.hpp>

#include <stdio.h>

#include <round/common/Properties.h>

using namespace std;
using namespace Round;

#define FRACTAL_DICTIONARY_BASIC_TEST_COUNT 100

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(RoundPropertiesBasicTest) {
  Properties dict;

  BOOST_CHECK_EQUAL(dict.size(), 0);

  char propName[32], propValue[32];

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(propName, sizeof(propName), "test%d", n);
    snprintf(propValue, sizeof(propValue), "%d", n);
  
    string retValue;
    BOOST_CHECK_EQUAL(dict.hasProperty(propName), false);
    BOOST_CHECK(dict.getProperty(propName, &retValue));
    BOOST_CHECK_EQUAL(retValue.length(), 0);
  
    BOOST_CHECK(dict.getProperty(propName, &retValue, "hello"));
    BOOST_CHECK(0 < retValue.length());
    BOOST_CHECK_EQUAL(retValue.compare("hello"), 0);
  
    dict.setProperty(propName, propValue);
  
    BOOST_CHECK_EQUAL(dict.hasProperty(propName), true);
    BOOST_CHECK(dict.getProperty(propName, &retValue));
    BOOST_CHECK(0 < retValue.length());
    BOOST_CHECK_EQUAL(retValue.compare(propValue), 0);
  }
}

BOOST_AUTO_TEST_SUITE_END()

