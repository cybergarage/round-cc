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

const char *Round::JSONInteger::toJSONString(std::string *stringBuf) const {
  *stringBuf = this->c_str();
  return stringBuf->c_str();
}
