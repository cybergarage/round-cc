/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/common/Properties.h>

////////////////////////////////////////////////
//  Properties
////////////////////////////////////////////////

Round::Properties::Properties() {
}

Round::Properties::~Properties() {
}

void Round::Properties::setProperty(const std::string &key, const std::string &value) {
  set(key, value);
}

bool Round::Properties::hasProperty(const std::string &key) {
  std::string value;
  return get(key, &value);
}

const char *Round::Properties::getProperty(const std::string &key, std::string *value, const std::string &defaultValue) {
  bool hasProperty = get(key, value);

  if (hasProperty == false)
    *value = defaultValue;

  return value->c_str();
}
