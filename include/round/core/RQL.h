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
#include <round/core/Node.h>

namespace Round {

namespace HTTP {
static const std::string ENDPOINT     = "/rql";
static const std::string QUERY        = "query";
}
  
class RQLParser  : public uSQL::SQLParser {

public:

  RQLParser();

  bool parse(const std::string &query);
};

class RQLRequest : public NodeRequest {
public:
    
  RQLRequest();
    
  bool parseQuery(const std::string &query, Error *err);

private:
  bool parseRpcQuery(const std::string &query, Error *err);
};
  
}

#endif
