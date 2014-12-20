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

bool Round::JSON::IsNumeric(const std::string &strValue) {
  size_t strLen = strValue.length();
  for (size_t n=0; n<strLen; n++) {
    if (!isnumber(strValue[n]) && (strValue[n] != '-'))
      return false;
  }
  return true;
}

Round::JSONInteger::JSONInteger() {
}

Round::JSONInteger::JSONInteger(int value) {
  set(value);
}
