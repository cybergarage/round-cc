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

#include <round/common/JSON.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(json)

////////////////////////////////////////////////////////////
// Root Object
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParsePopRootObjectTest) {
  Error error;
  JSONParser *jsonParser = new JSONParser();
  
  BOOST_CHECK(jsonParser->parse("[0, 1, 2]", &error));
  BOOST_CHECK(jsonParser->getRootObject());
  BOOST_CHECK(jsonParser->getRootObject()->isArray());
  
  JSONArray *jsonArray, *popJsonArray;

  jsonArray = dynamic_cast<JSONArray *>(jsonParser->getRootObject());
  BOOST_CHECK(jsonArray);
  
  popJsonArray = dynamic_cast<JSONArray *>(jsonParser->popRootObject());
  BOOST_CHECK(popJsonArray);
  
  jsonArray = dynamic_cast<JSONArray *>(jsonParser->getRootObject());
  BOOST_CHECK(!jsonArray);
  
  delete jsonParser;
  
  BOOST_CHECK_EQUAL(popJsonArray->size(), 3);
  for (int n=0; n<3; n++) {
    int value;
    BOOST_CHECK(popJsonArray->getInteger(n, &value));
    BOOST_CHECK_EQUAL(value, n);
  }
  
  delete popJsonArray;
}

////////////////////////////////////////////////////////////
// For Array
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseNumberArrayTest) {
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("[0, 1, 2]", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 3);
  
  for (int n=0; n<3; n++) {
    int value;
    BOOST_CHECK(jsonArray->getInteger(n, &value));
    BOOST_CHECK_EQUAL(value, n);
  }
}

BOOST_AUTO_TEST_CASE(JSONParseStringArrayTest) {
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("[\"milk\", \"bread\", \"eggs\"]", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
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

BOOST_AUTO_TEST_CASE(JSONParseAStringWithSpaceArrayTest) {
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("[\"name\", \"John Smith\"]", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK_EQUAL(jsonArray->size(), 2);

  string value;

  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("name"), 0);

  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("John Smith"), 0);
}

////////////////////////////////////////////////////////////
// For Dictionary
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseNumberDictionaryTest) {
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"a\": 1, \"b\": 2}", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonDict);
  BOOST_CHECK_EQUAL(jsonDict->size(), 2);
  string value;
  int intValue;
  BOOST_CHECK(jsonDict->get("a", &intValue));
  BOOST_CHECK_EQUAL(intValue, 1);
  BOOST_CHECK(jsonDict->get("b", &intValue));
  BOOST_CHECK_EQUAL(intValue, 2);
}

BOOST_AUTO_TEST_CASE(JSONParseStringDictionaryTest) {
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 32}", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonDict);
  BOOST_CHECK_EQUAL(jsonDict->size(), 2);
  string value;
  int intValue;
  BOOST_CHECK(jsonDict->get("name", &value));
  BOOST_CHECK_EQUAL(value.compare("John Smith"), 0);
  BOOST_CHECK(jsonDict->get("age", &value));
  BOOST_CHECK_EQUAL(value.compare("32"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 32);
}

////////////////////////////////////////////////////////////
// For Dictionary in Array
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseDictionaryInArrayTest01) {
  const char *testString = "[ {\"age\":\"32\",\"name\":\"John Smith\"},{\"age\":\"31\",\"name\":\"John Lennon\"} ]";
  
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());

  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
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
  BOOST_CHECK_EQUAL(strValue.compare("32"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 32);

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
  const char *testString = "[\n{\"age\":\"32\",\"name\":\"John Smith\"},\n{\"age\":\"31\",\"name\":\"John Lennon\"}\n]";
  
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());

  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
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
  BOOST_CHECK_EQUAL(strValue.compare("32"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 32);

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
  
  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString, &error));

  string jsonString;

  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
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

  Error error;
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testJSONValue, &error));

  JSONObject *jsonValueObject = jsonParser.getRootObject();
  BOOST_CHECK(jsonValueObject);
  BOOST_CHECK(jsonValueObject->isDictionary());

  JSONDictionary *jsonValueDict = static_cast<JSONDictionary *>(jsonValueObject);
  std::string jsonString;
  jsonValueDict->toJSONString(&jsonString);
  BOOST_CHECK_EQUAL(jsonString.compare(testJSONValue), 0);
}

////////////////////////////////////////////////////////////
// For Serialization
////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(JSONParseArraySerialize) {
  const char *testString = "[\"milk\",\"bread\",\"eggs\"]";

  JSONParser jsonParser;
  JSONArray *jsonArray;
  string value;
  Error error;
  
  BOOST_CHECK(jsonParser.parse(testString, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  
  // Serialize
  
  jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  jsonArray->toJSONString(&value);
  BOOST_CHECK_EQUAL(value.compare(testString), 0);

  // Reload Serialized string
  
  BOOST_CHECK(jsonParser.parse(value, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  
  jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("milk"), 0);
  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("bread"), 0);
  BOOST_CHECK(jsonArray->getString(2, &value));
  BOOST_CHECK_EQUAL(value.compare("eggs"), 0);
}


BOOST_AUTO_TEST_CASE(JSONParseDictionarySerialization) {
  const char *testString = "{\"age\":\"32\",\"name\":\"John Smith\"}";
  
  Error error;
  JSONDictionary *jsonDict;
  string value;
  int intValue;
  
  JSONParser jsonParser;
  BOOST_CHECK(jsonParser.parse(testString, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());

  // Serialize
  
  jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonDict);
  jsonDict->toJSONString(&value);
  BOOST_CHECK_EQUAL(value.compare(testString), 0);

  // Reload Serialized string
  
  BOOST_CHECK(jsonParser.parse(value, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  
  jsonDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonDict);
  BOOST_CHECK_EQUAL(jsonDict->size(), 2);
  BOOST_CHECK(jsonDict->get("name", &value));
  BOOST_CHECK_EQUAL(value.compare("John Smith"), 0);
  BOOST_CHECK(jsonDict->get("age", &value));
  BOOST_CHECK_EQUAL(value.compare("32"), 0);
  BOOST_CHECK(jsonDict->get("age", &intValue));
  BOOST_CHECK_EQUAL(intValue, 32);
}

BOOST_AUTO_TEST_CASE(JSONParseEscapedArraySerialize) {
  const char *testString = "[\"\\\"\\\"\",\"{}\"]";
  
  JSONParser jsonParser;
  JSONArray *jsonArray;
  string value;
  Error error;
  
  BOOST_CHECK(jsonParser.parse(testString, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  
  jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("\"\""), 0);
  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("{}"), 0);
  
  // Serialize
  
  jsonArray->toJSONString(&value);
  BOOST_CHECK_EQUAL(value.compare(testString), 0);
  
  // Reload Serialized string
  
  BOOST_CHECK(jsonParser.parse(value, &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isArray());
  
  jsonArray = dynamic_cast<JSONArray *>(jsonParser.getRootObject());
  BOOST_CHECK(jsonArray);
  BOOST_CHECK(jsonArray->getString(0, &value));
  BOOST_CHECK_EQUAL(value.compare("\"\""), 0);
  BOOST_CHECK(jsonArray->getString(1, &value));
  BOOST_CHECK_EQUAL(value.compare("{}"), 0);
}

BOOST_AUTO_TEST_SUITE_END()
