/******************************************************************
*
* Round for C++
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
  clear();
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
    else {
      paramEndIdx = query.find_first_of(Console::method::PARAM_END, paramBeginIdx);
    }
  }
  
  if (paramEndIdx == std::string::npos) {
    err->setMessage(query);
    return false;
  }
  
  std::string method = query.substr(0, paramBeginIdx);
  
  std::string object;
  if (paramSepIdx != std::string::npos) {
    object = query.substr((paramBeginIdx+1), (paramSepIdx - paramBeginIdx - 1));
  }
  else {
    object = query.substr((paramBeginIdx+1), (paramEndIdx - paramBeginIdx - 1));
  }
  
  std::string params;
  if (paramSepIdx != std::string::npos) {
    params = query.substr((paramSepIdx+1), (paramEndIdx - paramSepIdx - 1));
  }
  
  boost::trim(method);
  boost::trim(object);
  boost::trim(params);

  if (method.length() <= 0) {
    return false;
  }
  setMethod(method);
  
  if (object.length() <= 0) {
    return false;
  }
  setDest(object);

  if (0 < params.length()) {
    setParams(params);
  }
  
  return true;
}
