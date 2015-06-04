/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
