/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <stdlib.h>

#include <round/common/JSON.h>

inline bool isNumeric(const std::string &strValue) {
  size_t strLen = strValue.length();
  for (size_t n=0; n<strLen; n++) {
    if (!isnumber(strValue[n]) && (strValue[n] != '-'))
      return false;
  }
  return true;
}

Round::JSONDictionary::JSONDictionary() {
}

Round::JSONDictionary::~JSONDictionary() {
  clear();
}

bool Round::JSONDictionary::set(const std::string &key, JSONObject *value) {
if (key.length() <= 0)
    return false;
  JSONDictionary::iterator map = find(key);
  if (map == end()) {
    insert(std::make_pair(key, value));
  }
  else {
    if (map->second)
      delete map->second;
    map->second = value;
  }

  return true;
}

bool Round::JSONDictionary::get(const std::string &key, JSONObject **value) const {
  *value = NULL;

  JSONDictionary::const_iterator dict = find(key);
  if (dict == end())
    return false;
  *value = dict->second;
  return true;
}

bool Round::JSONDictionary::hasKey(const std::string &key) const {
  return (find(key) != end()) ? true : false;
}

bool Round::JSONDictionary::set(const std::string &key, const std::string &value) {
  JSONString *jsonString = new JSONString(value);
  return set(key, jsonString);
}

bool Round::JSONDictionary::set(const std::string &key, const char *value) {
  return set(key, (const std::string &)value);
}

bool Round::JSONDictionary::set(const std::string &key, size_t value) {
  std::stringstream ss;
  ss << value;
  return set(key, ss.str());
}

bool Round::JSONDictionary::set(const std::string &key, int value) {
  std::stringstream ss;
  ss << value;
  return set(key, ss.str());
}

bool Round::JSONDictionary::set(const std::string &key, long value) {
  std::stringstream ss;
  ss << value;
  return set(key, ss.str());
}

bool Round::JSONDictionary::set(const std::string &key, bool value) {
  int intValue = value ? 1 : 0;
  return set(key, intValue);
}

bool Round::JSONDictionary::get(const std::string &key, std::string *value) const {
  JSONObject *jsonObj = NULL;
  if (get(key, &jsonObj) == false)
    return false;
  jsonObj->toJSONString(value);
  return true;
}

bool Round::JSONDictionary::get(const std::string &key, std::size_t *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  if (!isNumeric(strValue))
    return false;

  *value = atol(strValue.c_str());
  
  return true;
}

bool Round::JSONDictionary::get(const std::string &key, int *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  if (!isNumeric(strValue))
    return false;

  *value = atoi(strValue.c_str());
  
  return true;
}

bool Round::JSONDictionary::get(const std::string &key, long *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  if (!isNumeric(strValue))
    return false;
  
  *value = atol(strValue.c_str());
  
  return true;
}

bool Round::JSONDictionary::get(const std::string &key, bool *value) const {
  int intValue;
  if (get(key, &intValue) == false)
    return false;
  *value = (intValue == 0) ? false : true;
  return true;
}

const char *Round::JSONDictionary::get(const std::string &key, std::string *value, const std::string &defaultValue) const {
  if (get(key, value) == false)
    *value = defaultValue;
  return value->c_str();
}

std::size_t Round::JSONDictionary::get(const std::string &key, std::size_t defaultValue) const {
  std::size_t value;
  if (get(key, &value) == false)
    value = defaultValue;
  return value;
}

int Round::JSONDictionary::get(const std::string &key, int defaultValue) const {
  int value;
  if (get(key, &value) == false)
    value = defaultValue;
  return value;
}

long Round::JSONDictionary::get(const std::string &key, long defaultValue) const {
  long value;
  if (get(key, &value) == false)
    value = defaultValue;
  return value;
}

bool Round::JSONDictionary::get(const std::string &key, bool defaultValue) const {
  bool value;
  if (get(key, &value) == false)
    value = defaultValue;
  return value;
}

const char *Round::JSONDictionary::toJSONString(std::string *stringBuf) const {
  std::ostringstream ss;
  ss << "{";
  for (JSONDictionary::const_iterator obj = begin(); obj != end(); obj++) {
    if (obj != begin())
      ss << ",";
    JSONObject *jsonObj = obj->second;
    std::string jsonObjString;
    jsonObj->toJSONString(&jsonObjString);
    ss << "\"" << obj->first << "\":";
    if (jsonObj->isString())
      ss << "\"";
    ss << jsonObjString;
    if (jsonObj->isString())
      ss << "\"";
  }
  ss << "}";
  *stringBuf = ss.str();
  return stringBuf->c_str();
}

bool Round::JSONDictionary::set(const JSONDictionary *srcDict) {
  if (!srcDict)
    return false;

  for (JSONDictionary::const_iterator dict = srcDict->begin(); dict != srcDict->end(); dict++) {
    JSONObject *valueObj = dict->second;
    if (!valueObj)
      return false;
    JSONObject *copyObj = NULL;
    if (!valueObj->copy(&copyObj)) 
      return false;
    set(dict->first, copyObj);
  }

  return true;
}

bool Round::JSONDictionary::copy(JSONObject **newObj) const {
  JSONDictionary *dstDict = new JSONDictionary();
  if (dstDict->set(this)) {
    *newObj = dstDict;
    return true;
  }
  delete dstDict;
  return false;
}

bool Round::JSONDictionary::remove(const std::string &key) {
  JSONDictionary
  ::iterator dict = find(key);
  if (dict == end())
    return false;
  erase(dict);
  return true;
}

void Round::JSONDictionary::clear() {
  for (JSONDictionary::iterator obj = begin(); obj != end(); obj++) {
    if (obj->second)
      delete obj->second;
  }

  std::map<std::string, JSONObject *>::clear();
}
