/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/JSON.h>

Round::JSONObject::JSONObject() {
}

Round::JSONObject::~JSONObject() {
}

bool Round::JSONObject::isNull() const {
  return (getType() == NIL) ? true : false;
}

bool Round::JSONObject::isString() const {
  return (getType() == STRING) ? true : false;
}

bool Round::JSONObject::isInteger() const {
  return (getType() == INTEGER) ? true : false;
}

bool Round::JSONObject::isReal() const {
  return (getType() == REAL) ? true : false;
}

bool Round::JSONObject::isBoolean() const {
  return (getType() == BOOLEAN) ? true : false;
}

bool Round::JSONObject::isArray() const {
  return (getType() == ARRAY) ? true : false;
}

bool Round::JSONObject::isDictionary() const {
  return (getType() == DICTIONARY) ? true : false;
}

bool Round::JSONObject::equals(const JSONObject *otherObject) const {
  if (!otherObject)
    return false;

  std::string thisString;
  this->toJSONString(&thisString);

  std::string otherString;
  otherObject->toJSONString(&otherString);

  return (thisString.compare(otherString) == 0) ? true : false;
}

bool Round::JSONObject::copy(JSONObject **newObj) const {
  if (getType() == STRING) {
    const JSONString *srcString = static_cast<const JSONString *>(this);
    JSONString *dstString = new JSONString();
    if (dstString->set(srcString)) {
      *newObj = dstString;
      return true;
    }
    delete dstString;
  }

  if (getType() == ARRAY) {
    const JSONArray *srcArray = static_cast<const JSONArray *>(this);
    JSONArray *dstArray = new JSONArray();
    if (dstArray->set(srcArray)) {
      *newObj = dstArray;
      return true;
    }
    delete dstArray;
  }

  if (getType() == DICTIONARY) {
    const JSONDictionary *srcDict = static_cast<const JSONDictionary *>(this);
    JSONDictionary *dstDict = new JSONDictionary();
    if (dstDict->set(srcDict)) {
      *newObj = dstDict;
      return true;
    }
    delete dstDict;
  }

  return false;
}

