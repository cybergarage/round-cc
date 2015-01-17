/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUND_BASE64_H_
#define _ROUND_BASE64_H_

#include <string>
#include <round/common/types.h>

namespace Round {

namespace Base64 {

ssize_t Encode(const byte *inBytes, size_t rawByteLen, std::string *encodedStr);
ssize_t Decode(const std::string &encodedStr, byte **decordedBytes);

}
  
}

#endif
