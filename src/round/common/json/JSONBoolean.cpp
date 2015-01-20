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

Round::JSONBoolean::JSONBoolean() {
}

Round::JSONBoolean::JSONBoolean(bool value) {
  set(value);
}

const char *Round::JSONBoolean::toJSONString(std::string *stringBuf) const {
  *stringBuf = this->c_str();
  return stringBuf->c_str();
}
