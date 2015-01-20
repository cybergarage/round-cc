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

#include <string>
#include <vector>

#include <limits.h>
#include <stdio.h>

#include <round/common/Dictionary.h>

using namespace std;
using namespace Round;

#define FRACTAL_DICTIONARY_BASIC_TEST_COUNT 10

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(RoundDictionaryStringTest) {
  Dictionary dict;

  string key = "key";
  string value;
  string valueBuf;

  value = "hello";
  dict.set(key, value);
  BOOST_CHECK(dict.get(key, &valueBuf));
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);

  value = "world";
  dict.set(key, value);
  BOOST_CHECK(dict.get(key, &valueBuf));
  BOOST_CHECK_EQUAL(valueBuf.compare(value), 0);
}

BOOST_AUTO_TEST_CASE(RoundDictionaryStringSetterTest) {
  Dictionary dict;

  string key = "key";
  std::string strValue = "value";

  string strBuf;
  BOOST_CHECK(dict.set(key, strValue));
  BOOST_CHECK(dict.get(key, &strBuf));
  BOOST_CHECK_EQUAL(strBuf.compare(strValue), 0);
}

BOOST_AUTO_TEST_CASE(RoundDictionaryIntegerMinMaxTest) {
  Dictionary dict;

  string key = "key";
  int value;

  value = -1;
  dict.set(key, (int)std::numeric_limits<int>::min());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<int>::min());

  value = -1;
  dict.set(key, (int)0);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, 0);

  value = -1;
  dict.set(key, (int)std::numeric_limits<int>::max());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<int>::max());
}

BOOST_AUTO_TEST_CASE(RoundDictionaryLongMinMaxTest) {
  Dictionary dict;

  const char *key = "key";
  long value;

  value = -1;
  dict.set(key, std::numeric_limits<long>::min());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<long>::min());

  value = -1;
  dict.set(key, (long)0);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, 0);

  value = -1;
  dict.set(key, (long)std::numeric_limits<long>::max());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<long>::max());
}

BOOST_AUTO_TEST_CASE(RoundDictionarySizetMinMaxTest) {
  Dictionary dict;
  
  const char *key = "key";
  size_t value;
  
  value = -1;
  dict.set(key, std::numeric_limits<size_t>::min());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<size_t>::min());
  
  value = -1;
  dict.set(key, (size_t)0);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, 0);
  
  value = -1;
  dict.set(key, std::numeric_limits<size_t>::max());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<size_t>::max());
}

BOOST_AUTO_TEST_CASE(RoundDictionaryDoubleMinMaxTest) {
  Dictionary dict;
  
  const char *key = "key";
  double value;
  
  value = -1;
  dict.set(key, std::numeric_limits<long>::min());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<long>::min());
  
  value = -1;
  dict.set(key, (long)0);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, 0);
  
  value = -1;
  dict.set(key, std::numeric_limits<long>::max());
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, std::numeric_limits<long>::max());
}

BOOST_AUTO_TEST_CASE(RoundDictionaryBooleanTest) {
  Dictionary dict;

  const char *key = "key";
  bool value;

  BOOST_CHECK(!dict.get(key, &value));

  value = false;
  dict.set(key, true);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, true);

  value = true;
  dict.set(key, false);
  BOOST_CHECK(dict.get(key, &value));
  BOOST_CHECK_EQUAL(value, false);
}

BOOST_AUTO_TEST_CASE(RoundDictionaryStringLoopTest) {
  Dictionary dict;

  BOOST_CHECK_EQUAL(dict.size(), 0);

  char key[32], value[32];

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    snprintf(value, sizeof(value), "%d", n);
  
    string valueString = value;
  
    dict.set(key, valueString);
    BOOST_CHECK_EQUAL(dict.size(), (n+1));
  
    string keyValue;
    BOOST_CHECK(dict.hasKey(key));
    BOOST_CHECK(dict.get(key, &keyValue));
    BOOST_CHECK(0 < keyValue.length());
    BOOST_CHECK_EQUAL(keyValue.compare(value), 0);
  
    //cout << key << " = " << keyValue->c_str() << endl;
  }

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    snprintf(value, sizeof(value), "%d", n);
  
    //cout << key << " = " << n << endl;
  
    string keyValue;
  
    //cout << n << " = " << dict.size() << endl;
  
    BOOST_CHECK_EQUAL(dict.size(), (FRACTAL_DICTIONARY_BASIC_TEST_COUNT - n));
    BOOST_CHECK(dict.hasKey(key));
    BOOST_CHECK(dict.get(key, &keyValue));
    BOOST_CHECK(0 < keyValue.length());
    BOOST_CHECK_EQUAL(keyValue.compare(value), 0);
  
    dict.remove(key);
    BOOST_CHECK_EQUAL(dict.size(), (FRACTAL_DICTIONARY_BASIC_TEST_COUNT - (n + 1)));
    BOOST_CHECK(!dict.hasKey(key));
    BOOST_CHECK(!dict.get(key, &keyValue));
    BOOST_CHECK_EQUAL(keyValue.length(), 0);
  }

  BOOST_CHECK_EQUAL(dict.size(), 0);
}

BOOST_AUTO_TEST_CASE(RoundDictionaryIntegerLoopTest) {
  Dictionary dict;

  BOOST_CHECK_EQUAL(dict.size(), 0);

  char key[32];

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
  
    dict.set(key, n);
    BOOST_CHECK_EQUAL(dict.size(), (n+1));
  
    int keyValue;
    BOOST_CHECK(dict.get(key, &keyValue));
    BOOST_CHECK_EQUAL(keyValue, n);
  }

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
  
    int keyValue;  
    BOOST_CHECK_EQUAL(dict.size(), (FRACTAL_DICTIONARY_BASIC_TEST_COUNT - n));
    BOOST_CHECK(dict.get(key, &keyValue));
    BOOST_CHECK_EQUAL(keyValue, n);
  
    dict.remove(key);
    BOOST_CHECK_EQUAL(dict.size(), (FRACTAL_DICTIONARY_BASIC_TEST_COUNT - (n + 1)));
    BOOST_CHECK(!dict.get(key, &keyValue));
  }

  BOOST_CHECK_EQUAL(dict.size(), 0);
}

BOOST_AUTO_TEST_CASE(RoundDictionarySetLoopTest) {
  Dictionary dict01;

  char key[32];
  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    dict01.set(key, n);
  }

  Dictionary dict02;
  BOOST_CHECK_EQUAL(dict02.set(NULL), false);
  BOOST_CHECK_EQUAL(dict02.set(&dict01), true);
  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    int keyValue;
    BOOST_CHECK(dict02.get(key, &keyValue));
    BOOST_CHECK_EQUAL(keyValue, n);
  }
}

BOOST_AUTO_TEST_CASE(RoundDictionaryGetAllKeysTest) {
  Dictionary dict;

  char key[32];
  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    dict.set(key, n);
  }

  DictionaryKeyList keyList;
  BOOST_CHECK_EQUAL(dict.getAllKeys(&keyList), FRACTAL_DICTIONARY_BASIC_TEST_COUNT);
  BOOST_CHECK_EQUAL(keyList.size(), FRACTAL_DICTIONARY_BASIC_TEST_COUNT);

  for (int n = 0; n < FRACTAL_DICTIONARY_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "test%d", n);
    BOOST_CHECK(keyList.hasKey(key));
  }
}

BOOST_AUTO_TEST_SUITE_END()

