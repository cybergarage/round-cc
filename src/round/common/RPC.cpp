/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <map>
#include <round/common/RPC.h>
#include <uhttp/HTTP.h>

/*
 * JSON-RPC over HTTP
 * http://jsonrpc.org/historical/json-rpc-over-http.html
 */

static std::map<int, std::string> gJsonRpcErrorStrings;

int Round::RPC::JSON::HTTP::ErrorCodeToHTTPStatus(int jsonErrorCode) {
  switch (jsonErrorCode) {
    case RPC::JSON::ErrorCodeParserError :
    case RPC::JSON::ErrorCodeInvalidParams :
    case RPC::JSON::ErrorCodeInternalError :
      return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
    case RPC::JSON::ErrorCodeInvalidRequest :
      return uHTTP::HTTP::BAD_REQUEST;
    case RPC::JSON::ErrorCodeMethodNotFound :
      return uHTTP::HTTP::NOT_FOUND;
  }
  
  if (IsServerErrorCode(jsonErrorCode)) {
    return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
  }
  
  return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
}

const std::string &Round::RPC::JSON::ErrorCodeToString(int jsonErrorCode) {
  
  if (gJsonRpcErrorStrings.size() <= 0) {
    gJsonRpcErrorStrings[ErrorCodeUnknown]        = "Unknown Error";
    gJsonRpcErrorStrings[ErrorCodeParserError]    = "Parse error";
    gJsonRpcErrorStrings[ErrorCodeInvalidRequest] = "Invalid Request";
    gJsonRpcErrorStrings[ErrorCodeMethodNotFound] = "Method not found";
    gJsonRpcErrorStrings[ErrorCodeInvalidParams]  = "Invalid params";
    gJsonRpcErrorStrings[ErrorCodeInternalError]  = "Internal error";
    gJsonRpcErrorStrings[ErrorCodeServerError]    = "Server error";
  }

  if (IsServerErrorCode(jsonErrorCode)) {
    jsonErrorCode = ErrorCodeServerError;
  }
  else if (gJsonRpcErrorStrings.find(jsonErrorCode) == gJsonRpcErrorStrings.end()) {
    jsonErrorCode = ErrorCodeUnknown;
  }

  return gJsonRpcErrorStrings[jsonErrorCode];
}

bool Round::RPC::JSON::IsServerErrorCode(int jsonErrorCode) {
  if (jsonErrorCode < RPC::JSON::ErrorCodeServerErrorMin)
    return false;
  
  if (RPC::JSON::ErrorCodeServerErrorMax < jsonErrorCode)
    return false;
  
  return true;
}
