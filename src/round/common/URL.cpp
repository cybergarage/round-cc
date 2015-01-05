/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>

#include <round/common/URL.h>

bool Round::URL::Encode(const std::string &sourceStr, std::string *encodedStr) {
  std::ostringstream encodedBuf;
  size_t sourceStrLen = sourceStr.length();
  for (size_t n = 0; n<sourceStrLen; n++) {
    char c = sourceStr[n];
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encodedBuf << c;
      continue;
    }
    encodedBuf << "%" << std::hex << std::setw(2) << int((unsigned char)c);
  }
  *encodedStr = encodedBuf.str();
  return true;
}

bool Round::URL::Decode(const std::string &encodedStr, std::string *decordedStr) {
  size_t encodedStrLen = encodedStr.length();
  for (size_t n = 0; n<encodedStrLen; n++) {
    if (encodedStr[n] == '%') {
      if ((n + 3) <= encodedStrLen) {
        try {
          std::string hexValue = "0x" + encodedStr.substr(n + 1, 2);
          int value = boost::lexical_cast<int>(hexValue);
          *decordedStr += static_cast<char>(value);
          n += 2;
        } catch(boost::bad_lexical_cast &) {
          return false;
        }
      } else {
        return false;
      }
    } else if (encodedStr[n] == '+') {
      *decordedStr += ' ';
    } else {
      *decordedStr += encodedStr[n];
    }
  }
  return true;
}
