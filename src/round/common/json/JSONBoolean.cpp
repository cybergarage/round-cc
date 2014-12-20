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

Round::JSONBoolean::JSONBoolean() {
}

Round::JSONBoolean::JSONBoolean(bool value) {
  set(value);
}

bool Round::JSONBoolean::set(bool value) {
  std::stringstream ss;
  ss << value;
  return JSONString::set(ss.str());
}

bool Round::JSONBoolean::get(bool *value) const {
  std::string strValue;
  if (JSONString::get(&strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  
  if (!JSON::IsNumeric(strValue))
    return false;
  
  *value = (atoi(strValue.c_str()) != 0) ? true : false;
  
  return true;
}
