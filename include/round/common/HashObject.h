/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_HASHOBJECT_H_
#define _ROUND_HASHOBJECT_H_

#include <string>

namespace Round {

class HashObject {
 public:
  static size_t GetHashCodeLength();
  static bool GetStartHashCode(std::string *hashCode);
  static bool GetEndHashCode(std::string *hashCode);

 public:
  HashObject();
  ~HashObject();

  virtual const char *getHashSeed(std::string *seedString) const = 0;
  virtual bool getHashCode(std::string *hashCode) const;

  int compare(const HashObject *object) const;
  
  int compare(const HashObject &object) const {
    return compare(&object);
  }

  int compare(const std::string &hashCode) const;
  
  bool equals(const HashObject *otherNode) const {
    return (compare(otherNode) == 0) ? true : false;
  }
  
  bool equals(const HashObject &otherNode) const {
    return equals(&otherNode);
  }

  bool equals(const std::string &hashCode) const {
    return (compare(hashCode) == 0) ? true : false;
  }
};

}

#endif
