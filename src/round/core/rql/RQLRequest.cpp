/******************************************************************
*
* uSQL for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/algorithm/string.hpp>

#include <round/core/RQL.h>
#include <round/ui/console/Command.h>

Round::RQLRequest::RQLRequest() {
}

bool Round::RQLRequest::parseQuery(const std::string &query, Error *err) {
  return parseRpcQuery(query, err);
}

bool Round::RQLRequest::parseRpcQuery(const std::string &query, Error *err) {
  size_t paramBeginIdx = query.find_first_of(Console::method::PARAM_BEGIN);
  size_t paramSepIdx = std::string::npos;
  size_t paramEndIdx = std::string::npos;
  if (paramBeginIdx != std::string::npos) {
    paramSepIdx = query.find_first_of(Console::method::PARAM_SEP, paramBeginIdx);
    if (paramSepIdx != std::string::npos) {
      paramEndIdx = query.find_first_of(Console::method::PARAM_END, paramSepIdx);
    }
  }
  
  if (paramEndIdx == std::string::npos) {
    err->setMessage(query);
    return false;
  }
  
  std::string method = query.substr(0, paramBeginIdx);
  std::string object = query.substr((paramBeginIdx+1), (paramSepIdx - paramBeginIdx - 1));
  std::string params = query.substr((paramSepIdx+1), (paramEndIdx - paramSepIdx - 1));
  
  boost::trim(method);
  boost::trim(object);
  boost::trim(params);

  setMethod(method);
  setDest(object);
  setParams(params);
  
  return true;
}
