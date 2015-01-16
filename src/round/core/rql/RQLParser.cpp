/******************************************************************
*
* uSQL for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <antlr3.h>
#include <round/core/RQL.h>

Round::RQLParser::RQLParser()
{
}

bool Round::RQLParser::parse(const std::string &queryString)
{
  bool parseResult = SQLParser::parse(queryString);
  setStatementType(uSQL::SQLStatement::UNQL);
  return parseResult;
}
