/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTAL_STRINGTOKENIZER_H_
#define _FRACTAL_STRINGTOKENIZER_H_

#include <string>
#include <vector>

namespace Round {
  
typedef std::vector<std::string> StringTokenList;

class StringTokenizer {
 public:
  StringTokenizer(const std::string &str, const std::string &delim);
  ~StringTokenizer();

  bool hasMoreTokens();

  const char *nextToken();
  const char *nextToken(const std::string &delim);

  std::size_t getTokens(StringTokenList *tokenList);

private:

  std::string strBuf;
  std::string strDelim;
  std::string strCurrToken;
  std::string strNextToken;
  std::string::size_type lastDelimPos;
  bool hasNextTokens;

};

}

#endif
