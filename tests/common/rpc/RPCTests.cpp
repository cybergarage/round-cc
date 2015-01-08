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

#include <iostream>
#include <round/common/RPC.h>
#include <round/common/Base64.h>
#include <round/common/URL.h>
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(rpc)

BOOST_AUTO_TEST_CASE(GetURLEncodeWithBase64Test) {
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
    byte *rawBytes = (byte *)(*testString).c_str();
    
    // Base64 Encode -> URL Encode
    byte *b64EncordBytes = rawBytes;
    size_t b64EcordByteLen = (*testString).length();
    std::string b64EncodedStr;
    BOOST_CHECK(0 <= Base64::Encode(b64EncordBytes, b64EcordByteLen, &b64EncodedStr));
    std::string urlEncodedStr;
    BOOST_CHECK(URL::Encode(b64EncodedStr, &urlEncodedStr));
    
    // URL Decode -> Base64 Dencode
    std::string urlDecordedStr;
    BOOST_CHECK(URL::Decode(urlEncodedStr, &urlDecordedStr));
    byte *b64DecordedBytes;
    size_t b64DecordedByteLen = Base64::Decode(urlDecordedStr, &b64DecordedBytes);
    BOOST_CHECK(0 <= b64DecordedByteLen);

    // Compare
    std::string b64DecordedString((const char *)b64DecordedBytes, b64DecordedByteLen);
    BOOST_CHECK_EQUAL((*testString).compare(b64DecordedString), 0);
    if ((*testString).compare(b64DecordedString) != 0) {
      BOOST_MESSAGE("\"" << (*testString) << "\"" << "is not equals \"" << b64DecordedString << "\"");
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
