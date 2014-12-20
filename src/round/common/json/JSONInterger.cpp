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
#include <sstream>

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

bool Round::JSONInteger::set(int value) {
  std::stringstream ss;
  ss << value;
  return JSONString::set(ss.str());
}


bool Round::JSONInteger::get(int *value) const {
  std::string strValue;
  if (JSONString::get(&strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  
  if (!JSON::IsNumeric(strValue))
    return false;
  
  *value = atoi(strValue.c_str());
  
  return true;
}
