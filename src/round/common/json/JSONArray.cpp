/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <stdlib.h>
#include <sstream>
#include <round/common/JSON.h>

Round::JSONArray::JSONArray() {
}

Round::JSONArray::~JSONArray() {
  clear();
}

void Round::JSONArray::add(JSONObject *value) {
  push_back(value);
}

void Round::JSONArray::add(const std::string &value) {
  JSONString *jsonString = new JSONString(value);
  add(jsonString);
}

Round::JSONObject *Round::JSONArray::getObject(size_t n) const  {
  return at(n);
}

bool Round::JSONArray::getString(size_t n, std::string *value) const {
  const JSONObject *jsonObj = getObject(n);
  if (!jsonObj)
    return false;
  if (!jsonObj->isString())
    return false;
  const JSONString *jsonString = static_cast<const JSONString *>(jsonObj);
  *value = jsonString->c_str();
  return true;
}

bool Round::JSONArray::getInteger(size_t n, int *value) const {
  std::string stringValue;
  if (getString(n, &stringValue) == false)
    return false;
  if (stringValue.length() <= 0)
    return false;
  *value = atoi(stringValue.c_str());
  return true;
}

const char *Round::JSONArray::toJSONString(std::string *stringBuf) const {
  std::stringstream ss;
  ss << "[";
  for (JSONArray::const_iterator obj = begin(); obj != end(); obj++) {
    if (obj != begin())
      ss << ",";
    std::string value;
    ss << "\"" << (*obj)->toJSONString(&value) << "\"";
  }
  ss << "]";
  *stringBuf = ss.str();
  return stringBuf->c_str();
}

bool Round::JSONArray::set(const JSONArray *srcArray) {
  for (JSONArray::const_iterator obj = srcArray->begin(); obj != srcArray->end(); obj++) {
    JSONObject *copyObj = NULL;
    if (!(*obj)->copy(&copyObj))
      continue;
    add(copyObj);
  }
  return true;
}

bool Round::JSONArray::copy(JSONObject **newObj) const {
  JSONArray *dstArray = new JSONArray();
  if (dstArray->set(this)) {
    *newObj = dstArray;
    return true;
  }
  delete dstArray;
  return false;
}

void Round::JSONArray::clear() {
  for (JSONArray::iterator obj = begin(); obj != end(); obj++)
    delete *obj;
  std::vector<JSONObject *>::clear();
}
