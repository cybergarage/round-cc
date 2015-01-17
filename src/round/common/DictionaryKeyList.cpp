/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <stdlib.h>
#include <sstream>
#include <round/common/Dictionary.h>

Round::DictionaryKeyList::DictionaryKeyList() {}

Round::DictionaryKeyList::~DictionaryKeyList() {}

void Round::DictionaryKeyList::addKey(const std::string &key)  {
  push_back(key);
}

bool Round::DictionaryKeyList::hasKey(const std::string &key) const {
  for (DictionaryKeyList::const_iterator it = begin(); it != end(); it++) {
    if (key.compare(*it) == 0)
      return true;
  }
  return false;
}
