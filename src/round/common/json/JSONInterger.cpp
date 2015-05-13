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

Round::JSONInteger::JSONInteger() {
}

Round::JSONInteger::JSONInteger(int value) {
  set(value);
}

Round::JSONInteger::JSONInteger(long value) {
  set(value);
}

bool Round::JSONInteger::copy(JSONObject **newObj) const {
  JSONInteger *dstObj = new JSONInteger();
  if (dstObj->set(this)) {
    *newObj = dstObj;
    return true;
  }
  delete dstObj;
  return false;
}

const char *Round::JSONInteger::toJSONString(std::string *stringBuf) const {
  *stringBuf = this->c_str();
  return stringBuf->c_str();
}
