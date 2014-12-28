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

#include <round/common/MD5.h>
#include <round/common/SHA.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(MD5FuncTest) {
  const std::string TEST_SOURCE = "abcdefghijklmnopqrstuvwxyz";
  
  std::string hashCode;
  MD5::Hash(TEST_SOURCE, &hashCode);
  BOOST_CHECK_EQUAL(hashCode.length(), MD5::DIGEST_STRING_LENGTH);
}

BOOST_AUTO_TEST_CASE(SHA1FuncTest) {
  const std::string TEST_SOURCE = "abcdefghijklmnopqrstuvwxyz";
  
  std::string hashCode;
  SHA1::Hash(TEST_SOURCE, &hashCode);
  BOOST_CHECK_EQUAL(hashCode.length(), SHA1::DIGEST_STRING_LENGTH);
}

BOOST_AUTO_TEST_CASE(SHA256FuncTest) {
  const std::string TEST_SOURCE = "abcdefghijklmnopqrstuvwxyz";
  
  std::string hashCode;
  SHA256::Hash(TEST_SOURCE, &hashCode);
  BOOST_CHECK_EQUAL(hashCode.length(), SHA256::DIGEST_STRING_LENGTH);
}

BOOST_AUTO_TEST_SUITE_END()
