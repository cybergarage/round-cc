/******************************************************************
*
* uSQL for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_RQL_H_
#define _ROUNDCC_RQL_H_

#include <usql/SQLParser.h>

namespace Round {

class RQLParser  : public uSQL::SQLParser {

public:

  RQLParser();

  bool parse(const std::string &queryString);
};

}

#endif
