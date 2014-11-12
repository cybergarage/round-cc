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

Round::JSONString::JSONString() {
}

Round::JSONString::JSONString(const std::string &value) {
  assign(value);
}

Round::JSONString::~JSONString() {
}

bool Round::JSONString::set(const JSONString *jsonObj) {
  assign(jsonObj->c_str());
  return true;
}

bool Round::JSONString::set(const std::string &value) {
  assign(value);
  return true;
}

bool Round::JSONString::copy(JSONObject **newObj) const {
  JSONString *dstString = new JSONString();
  if (dstString->set(this)) {
    *newObj = dstString;
    return true;
  }
  delete dstString;
  return false;
}

const char *Round::JSONString::toJSONString(std::string *stringBuf) const {
  *stringBuf = this->c_str();
  return stringBuf->c_str();
}
