/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <vector>
#include <sstream>

#include <stdio.h>

#include <round/common/JSON.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundJSONDictionarySetterTest) {
JSONDictionary dict;

  string key = "key";

  string strValue = "value";
  string strBuf;
  BOOST_CHECK(dict.set(key, strValue));
  BOOST_CHECK(dict.get(key, &strBuf));
  BOOST_CHECK_EQUAL(strValue.compare(strBuf), 0);

  int intValue = INT_MAX;
  int intBuf;
  BOOST_CHECK(dict.set(key, intValue));
  BOOST_CHECK(dict.get(key, &intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);

  long longValue = LONG_MAX;
  long longBuf;
  BOOST_CHECK(dict.set(key, longValue));
  BOOST_CHECK(dict.get(key, &longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);

  size_t sizeValue = LONG_MAX; //SIZE_MAX;
  size_t sizeBuf;
  BOOST_CHECK(dict.set(key, sizeValue));
  BOOST_CHECK(dict.get(key, &sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);

  bool boolValue = true;
  bool boolBuf;
  BOOST_CHECK(dict.set(key, boolValue));
  BOOST_CHECK(dict.get(key, &boolBuf));
  BOOST_CHECK_EQUAL(boolValue, boolBuf);
  boolValue = false;
  BOOST_CHECK(dict.set(key, boolValue));
  BOOST_CHECK(dict.get(key, &boolBuf));
  BOOST_CHECK_EQUAL(boolValue, boolBuf);
}

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryGetterDefaultTest) {
JSONDictionary dict;

  string key = "key";

  string strValue = "value";
  string defaultStrValue = "defaultValue";
  string strBuf;
  dict.get(key, &strBuf, defaultStrValue);
  BOOST_CHECK_EQUAL(strBuf.compare(defaultStrValue), 0);
  BOOST_CHECK(dict.set(key, strValue));
  dict.get(key, &strBuf, defaultStrValue);
  BOOST_CHECK_EQUAL(strBuf.compare(strValue), 0);

  int intValue = INT_MAX;
  int defaultIntValue = INT_MIN;
  BOOST_CHECK(dict.remove(key));
  BOOST_CHECK_EQUAL(dict.get(key, defaultIntValue), defaultIntValue);
  BOOST_CHECK(dict.set(key, intValue));
  BOOST_CHECK_EQUAL(dict.get(key, defaultIntValue), intValue);

  long longValue = LONG_MAX;
  long defaultLongValue = LONG_MIN;
  BOOST_CHECK(dict.remove(key));
  BOOST_CHECK_EQUAL(dict.get(key, defaultLongValue), defaultLongValue);
  BOOST_CHECK(dict.set(key, longValue));
  BOOST_CHECK_EQUAL(dict.get(key, defaultLongValue), longValue);

  size_t sizeValue = LONG_MAX;
  size_t defaultSizeValue = LONG_MIN;
  BOOST_CHECK(dict.remove(key));
  BOOST_CHECK_EQUAL(dict.get(key, defaultSizeValue), defaultSizeValue);
  BOOST_CHECK(dict.set(key, sizeValue));
  BOOST_CHECK_EQUAL(dict.get(key, defaultSizeValue), sizeValue);

  bool boolValue = true;
  bool defaultBoolValue = false;
  BOOST_CHECK(dict.remove(key));
  BOOST_CHECK_EQUAL(dict.get(key, defaultBoolValue), defaultBoolValue);
  BOOST_CHECK(dict.set(key, boolValue));
  BOOST_CHECK_EQUAL(dict.get(key, defaultBoolValue), boolValue);
}

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryStringSetterTest) {
JSONDictionary dict;

  string key = "key";
  const char *strValue = "value";

  string strBuf;
  BOOST_CHECK(dict.set(key, strValue));
  BOOST_CHECK(dict.get(key, &strBuf));
  BOOST_CHECK_EQUAL(strBuf.compare(strValue), 0);
}

BOOST_AUTO_TEST_CASE(RoundJSONStringCopyTest) {
const std::string testValue = "testValue";
  JSONString srcString;
  srcString.set(testValue);

  JSONString *dstString;
  BOOST_CHECK(srcString.copy(&dstString));
  BOOST_CHECK(srcString.equals(dstString));
}

BOOST_AUTO_TEST_CASE(RoundJSONArrayCopyTest) {
const int testValueCnt = 3;

  JSONArray srcArray;
  for (int n = 0; n < testValueCnt; n++) {
    ostringstream os;
    os << "testValue" << n;
    JSONString *srcString = new JSONString();
    srcString->set(os.str());
    srcArray.add(srcString);
  }

  JSONArray *dstArray;
  BOOST_CHECK(srcArray.copy(&dstArray));
  BOOST_CHECK(srcArray.equals(dstArray));
}

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryCopyTest) {
const std::string testKey = "testKey";
  const std::string testValue = "testValue";

  JSONDictionary srcDist;
  srcDist.set(testKey, testValue);

  JSONDictionary *dstDict;
  BOOST_CHECK(srcDist.copy(&dstDict));
  BOOST_CHECK(srcDist.equals(dstDict));
}
