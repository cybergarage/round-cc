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

#include <round/common/URL.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(URLEncodeTest) {
  std::vector<std::string> testStrings;
  
  testStrings.push_back("");
  testStrings.push_back("a");
  testStrings.push_back("ab");
  testStrings.push_back("abc");
  testStrings.push_back("0123456789");
  testStrings.push_back("abcdefghijklmnopqrstuvwxyz");
  testStrings.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  testStrings.push_back("+-=~`!@#$%^&*()_+{}[]|\\:;\"'<>,.?/");
  testStrings.push_back("あかさたなはまやらわん");
 
  for (std::vector<std::string>::iterator testString = testStrings.begin(); testString != testStrings.end(); testString++) {
    std::string sourceStr = *testString;
    std::string encodedStr;
    BOOST_CHECK(URL::Encode(sourceStr, &encodedStr));
    
    std::string decordedStr;
    BOOST_CHECK(URL::Decode(encodedStr, &decordedStr));
    
    BOOST_CHECK_EQUAL((*testString).compare(decordedStr), 0);
    if ((*testString).compare(decordedStr) != 0) {
      BOOST_MESSAGE("\"" << (*testString) << "\"" << "is not equals \"" << decordedStr << "\"");
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
