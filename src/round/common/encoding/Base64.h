/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_BASE64_H_
#define _ROUND_BASE64_H_

#include <string>
#include <round/common/types.h>

namespace Round {

class Base64 {
 public:
  static ssize_t Encode(const byte *inBytes, size_t rawByteLen, std::string *encodedStr);
  static ssize_t Decode(const std::string &encodedStr, byte **decordedBytes);
};

}

#endif
