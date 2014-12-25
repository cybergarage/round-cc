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
#include <stdlib.h>
#include <sstream>
#include <round/common/Dictionary.h>

Round::Dictionary::Dictionary() {
}

Round::Dictionary::~Dictionary() {
}

std::size_t Round::Dictionary::getAllKeys(DictionaryKeyList *keyList) const {
  for (Dictionary::const_iterator dict = begin(); dict != end(); dict++) {
    keyList->addKey(dict->first);
  }

  return keyList->size();
}

bool Round::Dictionary::set(Dictionary *srcDict)  {
  if (!srcDict)
    return false;
  
  for (Dictionary::iterator dict = srcDict->begin(); dict != srcDict->end(); dict++) {
    set(dict->first, dict->second);
  }
  return true;
}

bool Round::Dictionary::set(const std::string &key, const std::string &value) {
if (key.length() <= 0)
    return false;
  Dictionary::iterator map = find(key);
  if (map == end()) {
    insert(std::make_pair(key, value));
  }
  else {
    map->second = value;
  }
  return true;
}

bool Round::Dictionary::get(const std::string &key, std::string *value) const {
  Dictionary::const_iterator dict = find(key);
  if (dict == end()) {
    *value = "";
    return false;
  }
  *value = dict->second;
  return true;
}

bool Round::Dictionary::hasKey(const std::string &key) const {
  return (find(key) != end()) ? true : false;
}

bool Round::Dictionary::set(const std::string &key, int value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::Dictionary::set(const std::string &key, bool value) {
  int intValue = value ? 1 : 0;
  return set(key, intValue);
}

bool Round::Dictionary::set(const std::string &key, long value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::Dictionary::set(const std::string &key, size_t value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::Dictionary::set(const std::string &key, double value) {
  std::string strValue = boost::lexical_cast<std::string>(value);
  return set(key, strValue);
}

bool Round::Dictionary::get(const std::string &key, int *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  *value = boost::lexical_cast<int>(strValue);
  return true;
}

bool Round::Dictionary::get(const std::string &key, bool *value) const {
  int intValue;
  if (get(key, &intValue) == false)
    return false;
  *value = (intValue == 0) ? false : true;
  return true;
}

bool Round::Dictionary::get(const std::string &key, long *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  *value = boost::lexical_cast<long>(strValue);
  return true;
}

bool Round::Dictionary::get(const std::string &key, size_t *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  *value = boost::lexical_cast<size_t>(strValue);
  return true;
}

bool Round::Dictionary::get(const std::string &key, double *value) const {
  std::string strValue;
  if (get(key, &strValue) == false)
    return false;
  if (strValue.length() <= 0)
    return false;
  *value = boost::lexical_cast<double>(strValue);
  return true;
}

bool Round::Dictionary::remove(const std::string &key) {
  Dictionary::iterator dict = find(key);
  if (dict == end())
    return false;
  erase(dict);
  return true;
}
