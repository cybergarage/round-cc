/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <stdio.h>

#include <round/common/StringTokenizer.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(StringUtilTokenizerTests) {
  StringTokenizer *strToken;
  const char *token[] = { "abcde", "test", "skonno" };
  char tokenStr[128];
  int tokenCnt;

  sprintf(tokenStr, "%s", token[0]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 1);
  delete strToken;

  sprintf(tokenStr, "%s,%s,%s", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 3);
  delete strToken;

  sprintf(tokenStr, "%s,%s,%s,", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 3);
  delete strToken;

  sprintf(tokenStr, ",%s,%s,%s,", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 3);
  delete strToken;

  strToken = new StringTokenizer("*", ",");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, "*") == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 1);
  delete strToken;

  sprintf(tokenStr, "%s", token[0]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 1);
  delete strToken;

  sprintf(tokenStr, "%s,,%s,,%s", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 3);
  delete strToken;

  sprintf(tokenStr, "  %s,  %s,  %s,  ", token[0], token[1], token[2]);
  strToken = new StringTokenizer(tokenStr, ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, token[tokenCnt]) == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 3);
  delete strToken;

  strToken = new StringTokenizer("*", ", \n\t");
  tokenCnt = 0;
  while( strToken->hasMoreTokens() == true) {
    const char *tstr = strToken->nextToken();
    BOOST_CHECK(strcmp(tstr, "*") == 0);
    tokenCnt++;
  }
  BOOST_CHECK(tokenCnt == 1);
  delete strToken;
}

BOOST_AUTO_TEST_SUITE_END()

