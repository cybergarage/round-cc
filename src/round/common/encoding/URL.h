/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_URL_H_
#define _ROUND_URL_H_

#include <string>
#include <round/common/types.h>

namespace Round {

class URL {
 public:
  static bool Encode(const std::string &sourceStr, std::string *encodedStr);
  static bool Decode(const std::string &encodedStr, std::string *decordedStr);
};

}

#endif
