/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <iostream>
#include <sstream>

#include <round/common/JSON.h>

static std::string JSON_ARRAY_TRIMS = "[], \n\t";
static std::string JSON_ARRAY_BEGIN = "\", ";
static std::string JSON_ARRAY_END = "\",";
static std::string JSON_ARRAY_DIR_BIGIN = "{";
static std::string JSON_ARRAY_DIR_END = "}";

static std::string JSON_DIR_TRIMS = "{}, \n\t";
static std::string JSON_DIR_SEPS = ":,";
static std::string JSON_DIR_BEGIN = "\", :";
static std::string JSON_DIR_END = "\"";
static std::string JSON_DIR_ARRAY_BIGIN = "{";
static std::string JSON_DIR_ARRAY_END = "}";

static std::string JSON_KEY_TRIMS = "\" []:";
static std::string JSON_VAL_TRIMS = "\" ";

static void RoundJSONSeparateString(const std::string &str, const std::string &start, const std::string &end, std::vector<std::string> *result);
static void RoundJSONTrimString(const std::string &str, const std::string &trims, std::string *value);

Round::JSONParser::JSONParser() {
  this->jsonObject = NULL;
}

Round::JSONParser::~JSONParser() {
  clear();
}

void Round::JSONParser::clear() {
  if (this->jsonObject) {
    delete this->jsonObject;
    this->jsonObject = NULL;
  }
}

bool Round::JSONParser::parse(const std::string &jsonString, JSONArray *parentArray) {
if (jsonString.find(JSON_ARRAY_DIR_BIGIN) == 0) {
    std::vector<std::string> dirValues;
    RoundJSONSeparateString(jsonString, JSON_ARRAY_DIR_BIGIN, JSON_ARRAY_DIR_END, &dirValues);
    for (std::vector<std::string>::iterator dirVal = dirValues.begin(); dirVal != dirValues.end(); dirVal++) {
      JSONDictionary *jsonDict = createJSONDictionary();
      std::string values;
      RoundJSONTrimString(*dirVal, JSON_DIR_TRIMS, &values);
      parse(values, jsonDict);
      parentArray->push_back(jsonDict);
    }
    return true;
  }

  std::vector<std::string> values;
  RoundJSONSeparateString(jsonString, JSON_ARRAY_BEGIN, JSON_ARRAY_END, &values);
  for (std::vector<std::string>::iterator value = values.begin(); value != values.end(); value++) {
    std::string valString;
    RoundJSONTrimString(*value, JSON_VAL_TRIMS, &valString);
    JSONString *jsonString = createJSONString(valString);
    parentArray->push_back(jsonString);
  }

  return true;
}

bool Round::JSONParser::parse(const std::string &jsonString, JSONDictionary *parentDir) {
  std::size_t dirBeginIndex = 0;
  std::size_t dirColonIndex = jsonString.find_first_of(":", dirBeginIndex);
  while (dirColonIndex != std::string::npos) {
    std::string rawKey = std::string(jsonString, dirBeginIndex, (dirColonIndex - dirBeginIndex));
    std::string key;
    RoundJSONTrimString(rawKey, JSON_VAL_TRIMS, &key);
    std::size_t valueBeginIndex = jsonString.find_first_not_of(" \n\t", (dirColonIndex+1));
    if (valueBeginIndex == std::string::npos)
      break;
    std::size_t valueEndIndex = std::string::npos;
    char valueBeginChar = jsonString.at(valueBeginIndex);
    if (valueBeginChar == '[') {
      valueEndIndex = jsonString.find_first_of("]", (valueBeginIndex + 1));
      if (valueEndIndex != std::string::npos) {
        std::string arrayValue = std::string(jsonString, (valueBeginIndex + 1), (valueEndIndex - valueBeginIndex - 1));
        JSONArray *jsonArray = createJSONArray();
        if (parse(arrayValue, jsonArray))
          parentDir->set(key, jsonArray);
      }
    } else if (valueBeginChar == '\"') {
      valueEndIndex = jsonString.find_first_of("\"", (valueBeginIndex + 1));
      if (valueEndIndex != std::string::npos) {
        std::string stringValue = std::string(jsonString, (valueBeginIndex + 1), (valueEndIndex - valueBeginIndex - 1));
        JSONString *stringObj = createJSONString(stringValue);
        parentDir->set(key, stringObj);
      }
    } else if (valueBeginChar == '{') {
      std::size_t innerDirBeginIndex = valueBeginIndex;
      valueEndIndex = jsonString.find_first_of("}", (innerDirBeginIndex + 1));
      while (jsonString.find_first_of("{", (innerDirBeginIndex + 1)) < valueEndIndex) {
        innerDirBeginIndex = valueEndIndex;
        valueEndIndex = jsonString.find_first_of("}", (innerDirBeginIndex + 1));
      }
      if (valueEndIndex != std::string::npos) {
        std::string dirValue = std::string(jsonString, (valueBeginIndex + 1), (valueEndIndex - valueBeginIndex - 1));
        JSONDictionary *jsonDict = createJSONDictionary();
        if (parse(dirValue, jsonDict))
          parentDir->set(key, jsonDict);
      }
    } else {
      valueEndIndex = jsonString.find_first_not_of(" \n\t", valueBeginIndex);
      if (valueEndIndex != std::string::npos) {
        std::string stringValue = std::string(jsonString, valueBeginIndex, (valueEndIndex - valueBeginIndex + 1));
        JSONString *stringObj = createJSONString(stringValue);
        parentDir->set(key, stringObj);
      }
    }
    if (valueEndIndex == std::string::npos)
      break;
    dirBeginIndex = jsonString.find_first_not_of(", \n\t", (valueEndIndex + 1));
    if (dirBeginIndex == std::string::npos)
      break;
    dirColonIndex = jsonString.find_first_of(":", dirBeginIndex);
  }

  return true;
}

bool Round::JSONParser::parse(const std::string &jsonString, JSONObject **jsonRetObject) {
  clear();

  if (jsonString.size() <= 0)
    return false;

  // JSON Array
  if (jsonString.find("[") == 0) {
    JSONArray *jsonArray = createJSONArray();
    std::string values;
    RoundJSONTrimString(jsonString, JSON_ARRAY_TRIMS, &values);
    parse(values, jsonArray);
    *jsonRetObject = jsonArray;
    return true;
  }

  // JSON Dictionary
  if (jsonString.find("{") == 0) {
    JSONDictionary *jsonDict = createJSONDictionary();
    std::string values;
    RoundJSONTrimString(jsonString, JSON_DIR_TRIMS, &values);
    parse(values, jsonDict);
    *jsonRetObject = jsonDict;
    return true;
  }

  return false;
}

bool Round::JSONParser::parse(const std::string &jsonString) {
  return parse(jsonString, &this->jsonObject);
}

static void RoundJSONSeparateString(const std::string &str, const std::string &start, const std::string &end, std::vector<std::string> *result) {
  if(str.length() <= 0)
    return;

  //std::cout << str << std::endl;

  std::size_t beginIndex = str.find_first_not_of(start);
  if (beginIndex == std::string::npos)
    return;
  
  std::size_t lastIndex = str.find_first_of(end, (beginIndex + 1));
  while (lastIndex != std::string::npos) {
    //std::cout << beginIndex << ":" << lastIndex << " " << std::string(str, beginIndex, lastIndex - beginIndex + 1) << std::endl;
    result->push_back(std::string(str, beginIndex, lastIndex - beginIndex + 1));
    beginIndex = str.find_first_not_of(start, (lastIndex + 1));
    if (beginIndex == std::string::npos)
      break;
    lastIndex = str.find_first_of(end, (beginIndex + 1));
    if (lastIndex == std::string::npos)
      lastIndex = str.length() - 1;
  }
}

static void RoundJSONTrimString(const std::string &str, const std::string &trims, std::string *value) {
  if(str.length() <= 0) {
    *value = "";
    return;
  }

  std::size_t beginIndex = str.find_first_not_of(trims);
  std::size_t lastIndex = str.find_last_not_of(trims);
  if(beginIndex == std::string::npos || lastIndex == std::string::npos) {
    *value = "";
    return;
  }
  *value = std::string(str, beginIndex, lastIndex - beginIndex + 1);
}
