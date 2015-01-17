/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/lexical_cast.hpp>
#include <round/common/JSON.h>

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
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::JSONDictionary::set(const std::string &key, int value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::JSONDictionary::set(const std::string &key, long value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::JSONDictionary::set(const std::string &key, bool value) {
  int intValue = value ? 1 : 0;
  return set(key, intValue);
}

bool Round::JSONDictionary::set(const std::string &key, double value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::JSONDictionary::get(const std::string &key, std::string *value) const {
  JSONObject *jsonObj = NULL;
  if (get(key, &jsonObj) == false)
    return false;
  
  JSONString *jsonStr = dynamic_cast<JSONString *>(jsonObj);
  if (jsonStr) {
    *value = *jsonStr;
    return true;
  }
  
  jsonObj->toJSONString(value);
  
  return true;
}

bool Round::JSONDictionary::get(const std::string &key, JSONString **value) const {
  JSONObject *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  *value = dynamic_cast<JSONString *>(jsonObj);
  return (*value) ? true : false;
}

bool Round::JSONDictionary::get(const std::string &key, std::size_t *value) const {
  JSONString *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  return jsonObj->get(value);
}

bool Round::JSONDictionary::get(const std::string &key, int *value) const {
  JSONString *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  return jsonObj->get(value);
}

bool Round::JSONDictionary::get(const std::string &key, long *value) const {
  JSONString *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  return jsonObj->get(value);
}

bool Round::JSONDictionary::get(const std::string &key, bool *value) const {
  JSONString *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  return jsonObj->get(value);
}

bool Round::JSONDictionary::get(const std::string &key, double *value) const {
  JSONString *jsonObj;
  if (!get(key, &jsonObj))
    return false;
  return jsonObj->get(value);
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
    
    ss << "\"" << obj->first << "\":";
    
    JSONObject *jsonObj = obj->second;
    std::string jsonObjString;
    jsonObj->toJSONString(&jsonObjString);
    ss << jsonObjString;
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

Round::JSONDictionary *Round::JSONDictionary::getJSONDictionary(const std::string &key) {
  JSONObject *jsonObj = NULL;
  get(key, &jsonObj);
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (jsonDict)
    return jsonDict;
  
  jsonDict = new JSONDictionary();
  set(key, jsonDict);
  
  return jsonDict;
}

Round::JSONArray *Round::JSONDictionary::getJSONArray(const std::string &key) {
  JSONObject *jsonObj = NULL;
  get(key, &jsonObj);
  
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  set(key, jsonArray);
  
  return jsonArray;
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
