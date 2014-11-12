/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/StringTokenizer.h>

Round::StringTokenizer::StringTokenizer(const std::string &str, const std::string &delim) {
hasNextTokens = true;
  strBuf = str;
  strDelim = delim;
  lastDelimPos = std::string::npos;

  nextToken(delim);
}

Round::StringTokenizer::~StringTokenizer() {}

bool Round::StringTokenizer::hasMoreTokens() {
return hasNextTokens;
}

const char *Round::StringTokenizer::nextToken() {
return nextToken(strDelim.c_str());
}

const char *Round::StringTokenizer::nextToken(const std::string &delim) {
strCurrToken = strNextToken;

  std::string::size_type findStartDelimPos = (lastDelimPos == std::string::npos) ? 0 : (lastDelimPos+1);
  std::string::size_type startDelimPos = strBuf.find_first_not_of(delim, findStartDelimPos);
  if (startDelimPos == std::string::npos) {
    hasNextTokens = false;
    strNextToken = "";
    return strCurrToken.c_str();
  }

  std::string::size_type endDelimPos = strBuf.find_first_of(delim, startDelimPos);
  if (endDelimPos == std::string::npos)
    endDelimPos = strBuf.length();
  strNextToken = strBuf.substr(startDelimPos, endDelimPos-startDelimPos);

  lastDelimPos = endDelimPos;

  return strCurrToken.c_str();
}

std::size_t Round::StringTokenizer::getTokens(StringTokenList *tokenList) {
while (hasMoreTokens())
    tokenList->push_back(nextToken());
  return tokenList->size();
}
