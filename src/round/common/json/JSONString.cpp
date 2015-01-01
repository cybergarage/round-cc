/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/lexical_cast.hpp>
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

bool Round::JSONString::set(const char *value) {
  return set((const std::string &)value);
}

bool Round::JSONString::set(int value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return JSONString::set(strValue);
}

bool Round::JSONString::set(bool value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return JSONString::set(strValue);
}

bool Round::JSONString::set(long value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return JSONString::set(strValue);
}

bool Round::JSONString::set(size_t value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return JSONString::set(strValue);
}

bool Round::JSONString::set(double value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return JSONString::set(strValue);
}

bool Round::JSONString::get(std::string *value) const {
  *value = *this;
  return true;
}

bool Round::JSONString::get(int *value) const {
  std::string strValue;
  if (JSONString::get(&strValue) == false)
    return false;

  if (strValue.length() <= 0)
    return false;
  
  try {
    *value = boost::lexical_cast<int>(strValue);
  } catch(boost::bad_lexical_cast &) {
    return false;
  }
  
  return true;
}

bool Round::JSONString::get(bool *value) const {
  std::string strValue;
  if (JSONString::get(&strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  try {
    *value = boost::lexical_cast<bool>(strValue);
  } catch(boost::bad_lexical_cast &) {
    return false;
  }
  
  return true;
}

bool Round::JSONString::get(long *value) const {
  std::string strValue;
  if (get(&strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  try {
    *value = boost::lexical_cast<long>(strValue);
  } catch(boost::bad_lexical_cast &) {
    return false;
  }
  
  return true;
}

bool Round::JSONString::get(size_t *value) const {
  std::string strValue;
  if (get(&strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  try {
    *value = boost::lexical_cast<size_t>(strValue);
  } catch(boost::bad_lexical_cast &) {
    return false;
  }
  
  return true;
}

bool Round::JSONString::get(double *value) const {
  std::string strValue;
  if (get(&strValue) == false)
    return false;
  
  if (strValue.length() <= 0)
    return false;
  
  try {
    *value = boost::lexical_cast<double>(strValue);
  } catch(boost::bad_lexical_cast &) {
    return false;
  }
  
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
  *stringBuf = "\"";
  stringBuf->append(*this);
  stringBuf->append("\"");
  return stringBuf->c_str();
}
