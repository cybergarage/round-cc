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

Round::JSONReal::JSONReal() {
}

Round::JSONReal::JSONReal(double value) {
  set(value);
}

bool Round::JSONReal::copy(JSONObject **newObj) const {
  JSONReal *dstObj = new JSONReal();
  if (dstObj->set(this)) {
    *newObj = dstObj;
    return true;
  }
  delete dstObj;
  return false;
}

const char *Round::JSONReal::toJSONString(std::string *stringBuf) const {
  *stringBuf = this->c_str();
  return stringBuf->c_str();
}
