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
#include <sstream>
#include <round/common/HashObject.h>
#include <round/common/SHA.h>

size_t Round::HashObject::GetHashCodeLength() {
  return SHA256::DIGEST_STRING_LENGTH;
}

bool Round::HashObject::GetStartHashCode(std::string *hashCode) {
std::stringstream keyStrBuf;
  size_t hashCodeLength = GetHashCodeLength();
  for (int n = 0; n < hashCodeLength; n++)
    keyStrBuf << "0";
  *hashCode = keyStrBuf.str();

  return true;
}

bool Round::HashObject::GetEndHashCode(std::string *hashCode) {
  std::stringstream keyStrBuf;
  size_t hashCodeLength = GetHashCodeLength();
  for (int n = 0; n < hashCodeLength; n++)
    keyStrBuf << "F";
  *hashCode = keyStrBuf.str();

  return true;
}

Round::HashObject::HashObject() {
}

Round::HashObject::~HashObject() {
}

bool Round::HashObject::getHashCode(std::string *hashCode) const {
  std::string seedString;
  getHashSeed(&seedString);

  if (seedString.length() <= 0) {
    *hashCode = "";
    return false;
  }

  SHA256::Hash(seedString, hashCode);

  return true;
}

int Round::HashObject::compare(const std::string &otherHashCode) const {
  std::string thisHashCode;
  if (!getHashCode(&thisHashCode))
    return 0;
  return thisHashCode.compare(otherHashCode);
}

int Round::HashObject::compare(const Round::HashObject *otherObject) const {
  if (!otherObject)
    return 0;
  
  std::string otherHash;
  if (!otherObject->getHashCode(&otherHash))
    return 0;

  return compare(otherHash);
};




