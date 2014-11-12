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

#include <round/common/JSON.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(JSONParseArrayTest01) {
JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("[\"milk\", \"bread\", \"eggs\"]"));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isArray());
  JSONArray *jsonArray = static_cast<JSONArray *>(jsonParser.getObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 3);

  string value;

  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("milk"), 0);

  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("bread"), 0);

  BOOST_CHECK(jsonArray->getString(2, &value));
  BOOST_CHECK_EQUAL(value.compare("eggs"), 0);
}

BOOST_AUTO_TEST_CASE(JSONParseArrayTest02) {
JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("[\"name\", \"John Smith\"]"));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isArray());
  JSONArray *jsonArray = static_cast<JSONArray *>(jsonParser.getObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 2);

  string value;

  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("name"), 0);

  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("John Smith"), 0);
}

BOOST_AUTO_TEST_CASE(JSONParseArraySerialize) {
const char *testString = "[\"milk\",\"bread\",\"eggs\"]";
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isArray());
  JSONArray *jsonArray = static_cast<JSONArray *>(jsonParser.getObject());
  BOOST_CHECK(jsonArray);
  string value;
  jsonArray->toJSONString(&value);
  //cout << value << endl;
  BOOST_CHECK_EQUAL(value.compare(testString), 0);
}

BOOST_AUTO_TEST_CASE(JSONParseDictionaryTest01) {
JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}"));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isDictionary());
  JSONDictionary *jsonDict = static_cast<JSONDictionary *>(jsonParser.getObject());
  BOOST_CHECK(jsonDict);
  BOOST_CHECK_EQUAL(jsonDict->size(), 2);
  string value;
  int intValue;
  BOOST_CHECK(jsonDict->get("name", &value));
  BOOST_CHECK_EQUAL(value.compare("John Smith"), 0);
  BOOST_CHECK(jsonDict->get("age", &value));
  BOOST_CHECK_EQUAL(value.compare("33"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 33);
}

BOOST_AUTO_TEST_CASE(JSONParseDictionarySerialize) {
const char *testString = "{\"age\":\"33\",\"name\":\"John Smith\"}";
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isDictionary());
  JSONDictionary *jsonDict = static_cast<JSONDictionary *>(jsonParser.getObject());
  BOOST_CHECK(jsonDict);
  string value;
  jsonDict->toJSONString(&value);
  //cout << value << endl;
  BOOST_CHECK_EQUAL(value.compare(testString), 0);
}

BOOST_AUTO_TEST_CASE(JSONParseCheckParserObject) {
const char *testString = "[\"milk\",\"bread\",\"eggs\"]";
  JSONObject *jsonObject = NULL;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString, &jsonObject));
  BOOST_CHECK(jsonObject);
  BOOST_CHECK(!jsonParser.getObject());
  BOOST_CHECK(jsonObject->isArray());
  JSONArray *jsonArray = static_cast<JSONArray *>(jsonObject);
  BOOST_CHECK(jsonArray);
  delete jsonObject;
}

BOOST_AUTO_TEST_CASE(JSONParseDictionaryInArrayTest01) {
const char *testString = "[ {\"age\":\"33\",\"name\":\"John Smith\"},{\"age\":\"31\",\"name\":\"John Lennon\"} ]";
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isArray());

  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 2);

  const JSONDictionary *jsonDict;
  string strValue;
  int intValue;

  jsonDict = dynamic_cast<const JSONDictionary *>(jsonArray->getObject(0));
  BOOST_CHECK(jsonDict);
  BOOST_CHECK(jsonDict->get("name", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("John Smith"), 0);
  BOOST_CHECK(jsonDict->get("age", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("33"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 33);

  jsonDict = dynamic_cast<const JSONDictionary *>(jsonArray->getObject(1));
  BOOST_CHECK(jsonDict);
  BOOST_CHECK(jsonDict->get("name", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("John Lennon"), 0);
  BOOST_CHECK(jsonDict->get("age", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("31"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 31);
}

BOOST_AUTO_TEST_CASE(JSONParseDictionaryInArrayTest02) {
const char *testString = "[\n{\"age\":\"33\",\"name\":\"John Smith\"},\n{\"age\":\"31\",\"name\":\"John Lennon\"}\n]";
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));
  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isArray());

  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 2);

  const JSONDictionary *jsonDict;
  string strValue;
  int intValue;

  jsonDict = dynamic_cast<const JSONDictionary *>(jsonArray->getObject(0));
  BOOST_CHECK(jsonDict);
  BOOST_CHECK(jsonDict->get("name", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("John Smith"), 0);
  BOOST_CHECK(jsonDict->get("age", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("33"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 33);

  jsonDict = dynamic_cast<const JSONDictionary *>(jsonArray->getObject(1));
  BOOST_CHECK(jsonDict);
  BOOST_CHECK(jsonDict->get("name", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("John Lennon"), 0);
  BOOST_CHECK(jsonDict->get("age", &strValue));
  BOOST_CHECK_EQUAL(strValue.compare("31"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 31);
}

BOOST_AUTO_TEST_CASE(JSONParseArrayInDictionaryTest01) {
const char *testString = "{\"phoneNumber\": [\"212 555-1234\", \"646 555-4567\"]}";
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString));

  string jsonString;

  BOOST_CHECK(jsonParser.getObject());
  BOOST_CHECK(jsonParser.getObject()->isDictionary());
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getObject());
  BOOST_CHECK(jsonDict);

  jsonDict->toJSONString(&jsonString);
  //std::cout << jsonDict << std::endl;
  BOOST_CHECK_EQUAL(jsonDict->size(), 1);

  BOOST_CHECK(jsonDict->hasKey("phoneNumber"));
  JSONObject *phoneNumberObj = NULL;
  BOOST_CHECK(jsonDict->get("phoneNumber", &phoneNumberObj));
  BOOST_CHECK(phoneNumberObj);
  JSONArray *phoneNumberArray = dynamic_cast<JSONArray *>(phoneNumberObj);
  BOOST_CHECK_EQUAL(phoneNumberArray->size(), 2);

  string value;

  BOOST_CHECK(phoneNumberArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("212 555-1234"), 0);
  BOOST_CHECK(phoneNumberArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("646 555-4567"), 0);
 }

BOOST_AUTO_TEST_CASE(RoundJSONDictionaryParserTest) {
string testJSONValue = "{\"key\":\"value\"}";

  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testJSONValue));

  JSONObject *jsonValueObject = jsonParser.getObject();
  BOOST_CHECK(jsonValueObject);
  BOOST_CHECK(jsonValueObject->isDictionary());

  JSONDictionary *jsonValueDict = static_cast<JSONDictionary *>(jsonValueObject);
  std::string jsonString;
  jsonValueDict->toJSONString(&jsonString);
  BOOST_CHECK_EQUAL(jsonString.compare(testJSONValue), 0);
}


