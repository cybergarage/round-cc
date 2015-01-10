/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FRACTAL_SHA_H_
#define _FRACTAL_SHA_H_

#include <string>

namespace Round {
  
class SHA1 {
 public:
  static const int DIGEST_LENGTH;
  static const int DIGEST_STRING_LENGTH;
  static const char *Hash(const std::string &string, std::string *buf);
};

class SHA256 {
 public:
  static const int DIGEST_LENGTH;
  static const int DIGEST_STRING_LENGTH;
  static const char *Hash(const std::string &string, std::string *buf);
};

}

#endif
