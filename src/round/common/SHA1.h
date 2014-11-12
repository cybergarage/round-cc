/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FRACTAL_SHA1_H_
#define _FRACTAL_SHA1_H_

#include <string>

namespace Round {
  
class SHA1 {
 public:
  static const int DIGEST_LENGTH;
  static const char *hash(const std::string &string, std::string *buf);

};

}

#endif
