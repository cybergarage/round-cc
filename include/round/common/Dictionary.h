/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_DICTIONARY_H_
#define _ROUNDCC_DICTIONARY_H_

#include <string>
#include <map>
#include <vector>
#include <time.h>

#include <round/common/BitOption.h>

namespace Round {
  
class DictionaryKeyList : public std::vector<std::string> {
 public:
  DictionaryKeyList();
  virtual ~DictionaryKeyList();

  void addKey(const std::string &key);
  bool hasKey(const std::string &key) const;
};

class Dictionary : public std::map<std::string, std::string> {
 public:
  Dictionary();
  virtual ~Dictionary();

  bool hasKey(const std::string &key) const;
  std::size_t getAllKeys(DictionaryKeyList *keyList) const;
  
  bool set(Dictionary *dict);
  bool set(const std::string &key, const std::string &value);
  bool set(const std::string &key, int value);
  bool set(const std::string &key, long value);
  bool set(const std::string &key, bool value);
  bool set(const std::string &key, size_t value);
  bool set(const std::string &key, double value);

  bool get(const std::string &key, std::string *value) const;
  bool get(const std::string &key, int *value) const;
  bool get(const std::string &key, long *value) const;
  bool get(const std::string &key, bool *value) const;
  bool get(const std::string &key, size_t *value) const;
  bool get(const std::string &key, double *value) const;

  bool remove(const std::string &key);
};

}

#endif
