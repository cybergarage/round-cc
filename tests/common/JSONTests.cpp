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
#include <boost/algorithm/string.hpp>

#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include <stdio.h>

#include <round/common/JSON.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(json)

////////////////////////////////////////////////////////////
// JSONNull
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONNullTypeTest) {
  JSONNull jsonObj;
  
  BOOST_CHECK(jsonObj.isNull());
  BOOST_CHECK(dynamic_cast<JSONString *>(&jsonObj));
}

////////////////////////////////////////////////////////////
// JSONInteger
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONIntegerTypeTest) {
  JSONInteger jsonObj;
  
  BOOST_CHECK(jsonObj.isInteger());
  BOOST_CHECK(dynamic_cast<JSONInteger *>(&jsonObj));
  BOOST_CHECK(dynamic_cast<JSONString *>(&jsonObj));
}

BOOST_AUTO_TEST_CASE(RoundJSONIntergerSetterTest) {
  JSONInteger jsonObj;

  int value, retValue;
  
  value = std::numeric_limits<int>::min();
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);

  value = 0;
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
  
  value = std::numeric_limits<int>::max();
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
}

////////////////////////////////////////////////////////////
// JSONReal
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONRealTypeTest) {
  JSONReal jsonObj;
  
  BOOST_CHECK(jsonObj.isReal());
  BOOST_CHECK(dynamic_cast<JSONReal *>(&jsonObj));
  BOOST_CHECK(dynamic_cast<JSONString *>(&jsonObj));
}

BOOST_AUTO_TEST_CASE(RoundJSONRealSetterTest) {
  JSONReal jsonObj;
  
  double value, retValue;
  
  value = std::numeric_limits<double>::min();
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
  
  value = 0;
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
  
  value = std::numeric_limits<double>::max();
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
}

////////////////////////////////////////////////////////////
// JSONBoolean
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONBooleanTypeTest) {
  JSONBoolean jsonObj;
  
  BOOST_CHECK(jsonObj.isBoolean());
  BOOST_CHECK(dynamic_cast<JSONBoolean *>(&jsonObj));
  BOOST_CHECK(dynamic_cast<JSONString *>(&jsonObj));
}

BOOST_AUTO_TEST_CASE(RoundJSONBooleanSetterTest) {
  JSONBoolean jsonObj;
  
  bool value, retValue;
  
  value = true;
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);

  value = false;
  BOOST_CHECK(jsonObj.set(value));
  BOOST_CHECK(jsonObj.get(&retValue));
  BOOST_CHECK_EQUAL(value, retValue);
}

////////////////////////////////////////////////////////////
// JSONString
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONStringTypeTest) {
  JSONString jsonObj;
  
  BOOST_CHECK(jsonObj.isString());
  BOOST_CHECK(dynamic_cast<JSONString *>(&jsonObj));
}

BOOST_AUTO_TEST_CASE(RoundJSONStringSetterTest) {
  JSONString jsonObj;
  
  string key = "key";
  
  string strValue = "value";
  string strBuf;
  BOOST_CHECK(jsonObj.set(strValue));
  BOOST_CHECK(jsonObj.get(&strBuf));
  BOOST_CHECK_EQUAL(strValue.compare(strBuf), 0);
  
  int intValue;
  int intBuf;
  intValue = std::numeric_limits<int>::max();
  BOOST_CHECK(jsonObj.set(intValue));
  BOOST_CHECK(jsonObj.get(&intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);
  intValue = std::numeric_limits<int>::min();
  BOOST_CHECK(jsonObj.set(intValue));
  BOOST_CHECK(jsonObj.get(&intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);
  
  long longValue;
  long longBuf;
  longValue = std::numeric_limits<long>::max();
  BOOST_CHECK(jsonObj.set(longValue));
  BOOST_CHECK(jsonObj.get(&longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);
  longValue = std::numeric_limits<long>::min();
  BOOST_CHECK(jsonObj.set(longValue));
  BOOST_CHECK(jsonObj.get(&longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);
  
  size_t sizeBuf;
  size_t sizeValue;
  sizeValue = std::numeric_limits<size_t>::max();
  BOOST_CHECK(jsonObj.set(sizeValue));
  BOOST_CHECK(jsonObj.get(&sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);
  sizeValue = std::numeric_limits<size_t>::min();
  BOOST_CHECK(jsonObj.set(sizeValue));
  BOOST_CHECK(jsonObj.get(&sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);
  
  bool boolValue;
  bool boolBuf;
  boolValue = true;
  BOOST_CHECK(jsonObj.set(boolValue));
  BOOST_CHECK(jsonObj.get(&boolBuf));
  BOOST_CHECK_EQUAL(boolValue, boolBuf);
  boolValue = false;
  BOOST_CHECK(jsonObj.set(boolValue));
  BOOST_CHECK(jsonObj.get(&boolBuf));
  BOOST_CHECK_EQUAL(boolValue, boolBuf);
}

////////////////////////////////////////////////////////////
// JSONDictionary
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(RoundJSONDictionarySetterTest) {
  JSONDictionary dict;

  string key = "key";

  string strValue = "value";
  string strBuf;
  BOOST_CHECK(dict.set(key, strValue));
  BOOST_CHECK(dict.get(key, &strBuf));
  BOOST_CHECK_EQUAL(strValue.compare(strBuf), 0);

  int intValue;
  int intBuf;
  intValue = std::numeric_limits<int>::max();
  BOOST_CHECK(dict.set(key, intValue));
  BOOST_CHECK(dict.get(key, &intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);
  intValue = 0;
  BOOST_CHECK(dict.set(key, intValue));
  BOOST_CHECK(dict.get(key, &intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);
  intValue = std::numeric_limits<int>::min();
  BOOST_CHECK(dict.set(key, intValue));
  BOOST_CHECK(dict.get(key, &intBuf));
  BOOST_CHECK_EQUAL(intValue, intBuf);

  long longValue;
  long longBuf;
  longValue = std::numeric_limits<long>::max();
  BOOST_CHECK(dict.set(key, longValue));
  BOOST_CHECK(dict.get(key, &longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);
  longValue = 0;
  BOOST_CHECK(dict.set(key, longValue));
  BOOST_CHECK(dict.get(key, &longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);
  longValue = std::numeric_limits<long>::min();
  BOOST_CHECK(dict.set(key, longValue));
  BOOST_CHECK(dict.get(key, &longBuf));
  BOOST_CHECK_EQUAL(longValue, longBuf);

  size_t sizeBuf;
  size_t sizeValue;
  sizeValue = std::numeric_limits<size_t>::max();
  BOOST_CHECK(dict.set(key, sizeValue));
  BOOST_CHECK(dict.get(key, &sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);
  sizeValue = 0;
  BOOST_CHECK(dict.set(key, sizeValue));
  BOOST_CHECK(dict.get(key, &sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);
  sizeValue = std::numeric_limits<size_t>::min();
  BOOST_CHECK(dict.set(key, sizeValue));
  BOOST_CHECK(dict.get(key, &sizeBuf));
  BOOST_CHECK_EQUAL(sizeValue, sizeBuf);

  double realBuf;
  double realValue;
  realValue = std::numeric_limits<double>::max();
  BOOST_CHECK(dict.set(key, realValue));
  BOOST_CHECK(dict.get(key, &realBuf));
  BOOST_CHECK_EQUAL(realValue, realBuf);
  realValue = 0;
  BOOST_CHECK(dict.set(key, realValue));
  BOOST_CHECK(dict.get(key, &realBuf));
  BOOST_CHECK_EQUAL(realValue, realBuf);
  realValue = std::numeric_limits<double>::min();
  BOOST_CHECK(dict.set(key, realValue));
  BOOST_CHECK(dict.get(key, &realBuf));
  BOOST_CHECK_EQUAL(realValue, realBuf);
  
  bool boolValue;
  bool boolBuf;
  boolValue = true;
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

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryGetDirectoryTest) {
  string key = "key";
  
  JSONDictionary jsonDict;
  JSONObject *jsonObj;
  
  BOOST_CHECK(!jsonDict.get(key, &jsonObj));
  
  jsonObj = jsonDict.getJSONDictionary(key);
  BOOST_CHECK(jsonObj);
  BOOST_CHECK(dynamic_cast<JSONDictionary *>(jsonObj));

  BOOST_CHECK(jsonDict.get(key, &jsonObj));
  BOOST_CHECK(jsonObj);
  BOOST_CHECK(dynamic_cast<JSONDictionary *>(jsonObj));
}

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryGetArrayTest) {
  string key = "key";
  
  JSONDictionary jsonDict;
  JSONObject *jsonObj;
  
  BOOST_CHECK(!jsonDict.get(key, &jsonObj));
  
  jsonObj = jsonDict.getJSONArray(key);
  BOOST_CHECK(jsonObj);
  BOOST_CHECK(dynamic_cast<JSONArray *>(jsonObj));
  
  BOOST_CHECK(jsonDict.get(key, &jsonObj));
  BOOST_CHECK(jsonObj);
  BOOST_CHECK(dynamic_cast<JSONArray *>(jsonObj));
}

BOOST_AUTO_TEST_SUITE_END()
