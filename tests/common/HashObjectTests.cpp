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
#include <sstream>
#include <string.h>

#include <round/common/digest/SHA.h>
#include <round/common/HashObject.h>

using namespace std;
using namespace Round;

class TestHashObject : public HashObject {
public:
  TestHashObject(char value) {
    this->value = value;
  }
  
  const char *getHashSeed(std::string *seedString) const {
    return "";
  }
  
  bool getHashCode(std::string *hashCode) const {
    std::stringstream hashStrerm;
    for (int n=0; n<SHA256::DIGEST_LENGTH; n++)
      hashStrerm << this->value;
    *hashCode = hashStrerm.str();
    return true;
  }
  
private:
  char value;
  
};

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(HashObjectTests) {
  size_t hashCodeLength = HashObject::GetHashCodeLength();
  BOOST_CHECK(0 < hashCodeLength);
  BOOST_CHECK(0 < SHA256::DIGEST_STRING_LENGTH);

  stringstream startKeyStrBuf;
  for (int n = 0; n < hashCodeLength; n++)
    startKeyStrBuf << "0";
  string startKey = startKeyStrBuf.str();
  string startHashKey;
  BOOST_CHECK(HashObject::GetStartHashCode(&startHashKey));
  BOOST_CHECK_EQUAL(startKey.compare(startHashKey), 0);
  BOOST_CHECK_EQUAL(startKey.length(), hashCodeLength);

  stringstream endKeyStrBuf;
  for (int n = 0; n < hashCodeLength; n++)
    endKeyStrBuf << "F";
  string endtKey = endKeyStrBuf.str();
  string endHashKey;
  BOOST_CHECK(HashObject::GetEndHashCode(&endHashKey));
  BOOST_CHECK_EQUAL(endtKey.compare(endHashKey), 0);
  BOOST_CHECK_EQUAL(endtKey.length(), hashCodeLength);
}

BOOST_AUTO_TEST_CASE(HashObjectCompareTests) {
  TestHashObject testHash0('0');
  TestHashObject testHash1('1');
  TestHashObject testHashA('A');
  TestHashObject testHashF('F');

  BOOST_CHECK_EQUAL(testHash0.compare(testHash0), 0);
  BOOST_CHECK_EQUAL(testHash1.compare(testHash1), 0);
  BOOST_CHECK_EQUAL(testHashA.compare(testHashA), 0);
  BOOST_CHECK_EQUAL(testHashF.compare(testHashF), 0);
  
  BOOST_CHECK(testHash0.compare(testHash1) < 0);
  BOOST_CHECK(testHash0.compare(testHashA) < 0);
  BOOST_CHECK(testHash0.compare(testHashF) < 0);

  BOOST_CHECK(testHash1.compare(testHashA) < 0);
  BOOST_CHECK(testHash1.compare(testHashF) < 0);

  BOOST_CHECK(testHashA.compare(testHashF) < 0);
}

BOOST_AUTO_TEST_CASE(HashObjectEqualsTests) {
  TestHashObject testHash0('0');
  TestHashObject testHash1('1');
  TestHashObject testHashA('A');
  TestHashObject testHashF('F');
  
  BOOST_CHECK_EQUAL(testHash0.equals(testHash0), true);
  BOOST_CHECK_EQUAL(testHash1.equals(testHash1), true);
  BOOST_CHECK_EQUAL(testHashA.equals(testHashA), true);
  BOOST_CHECK_EQUAL(testHashF.equals(testHashF), true);
  
  BOOST_CHECK_EQUAL(testHash0.equals(testHash1), false);
  BOOST_CHECK_EQUAL(testHash0.equals(testHashA), false);
  BOOST_CHECK_EQUAL(testHash0.equals(testHashF), false);
  
  BOOST_CHECK_EQUAL(testHash1.equals(testHashA), false);
  BOOST_CHECK_EQUAL(testHash1.equals(testHashF), false);
  
  BOOST_CHECK_EQUAL(testHashA.equals(testHashF), false);

  string testHashCode0;
  string testHashCode1;
  string testHashCodeA;
  string testHashCodeF;
  
  BOOST_CHECK(testHash0.getHashCode(&testHashCode0));
  BOOST_CHECK_EQUAL(testHash0.equals(testHashCode0), true);
  
  BOOST_CHECK(testHash1.getHashCode(&testHashCode1));
  BOOST_CHECK_EQUAL(testHash1.equals(testHashCode1), true);

  BOOST_CHECK(testHashA.getHashCode(&testHashCodeA));
  BOOST_CHECK_EQUAL(testHashA.equals(testHashCodeA), true);

  BOOST_CHECK(testHashF.getHashCode(&testHashCodeF));
  BOOST_CHECK_EQUAL(testHashF.equals(testHashCodeF), true);
}

BOOST_AUTO_TEST_SUITE_END()
