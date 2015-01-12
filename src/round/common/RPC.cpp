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

int Round::RPC::JSON::HTTP::ErrorCodeToHTTPStatusCode(int jsonErrorCode) {
  // Standard Response Error Codes
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
  
  // Extended Parameter Error Codes
  switch (jsonErrorCode) {
    case RPC::JSON::ErrorCodeBadHashCode :
      return uHTTP::HTTP::BAD_REQUEST;
    case RPC::JSON::ErrorCodeMovedPermanently :
      return uHTTP::HTTP::MOVED_PERMANENTLY;
  }
  
  // Extented Parameter
  switch (jsonErrorCode) {
    case RPC::JSON::ErrorConditionFailed :
      return uHTTP::HTTP::NOT_ACCEPTABLE;
  }
  
  // Extended Script Engine Error Codes
  switch (jsonErrorCode) {
    case RPC::JSON::ErrorCodeScriptEngineInternalError :
    case RPC::JSON::ErrorCodeScriptCompileError :
    case RPC::JSON::ErrorCodeScriptRuntimeError :
      return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
    case RPC::JSON::ErrorCodeScriptEngineNotFound :
      return uHTTP::HTTP::BAD_REQUEST;
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
    
    gJsonRpcErrorStrings[ErrorCodeBadHashCode]      = "Bad Hash Length";
    gJsonRpcErrorStrings[ErrorCodeMovedPermanently] = "Moved Permanently";
    
    gJsonRpcErrorStrings[ErrorCodeScriptEngineInternalError]  = "Script Engine Internal Error";
    gJsonRpcErrorStrings[ErrorCodeScriptEngineNotFound]       = "Script Engine Not Found";
    gJsonRpcErrorStrings[ErrorCodeScriptCompileError]         = "Script Compile Error";
    gJsonRpcErrorStrings[ErrorCodeScriptRuntimeError]         = "Script Runtime Error";
    
    gJsonRpcErrorStrings[ErrorCodeServerError]    = "Server error";
  }

  if (gJsonRpcErrorStrings.find(jsonErrorCode) == gJsonRpcErrorStrings.end()) {
    if (IsServerErrorCode(jsonErrorCode)) {
      jsonErrorCode = ErrorCodeServerError;
    }
    else {
      jsonErrorCode = ErrorCodeUnknown;
    }
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

void Round::RPC::JSON::ErrorCodeToError(int jsonErrorCode, Error *error) {
  int httpStatusCode = HTTP::ErrorCodeToHTTPStatusCode(jsonErrorCode);
  error->setCode(httpStatusCode);
  error->setMessage(uHTTP::HTTP::StatusCodeToString(httpStatusCode));

  error->setDetailCode(jsonErrorCode);
  error->setDetailMessage(ErrorCodeToString(jsonErrorCode));
}
