/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <map>

#include <uhttp/HTTP.h>
#include <round/common/RPC.h>
#include <round/common/encoding/Base64.h>
#include <round/common/encoding/URL.h>

/*
 * JSON-RPC over HTTP
 * http://jsonrpc.org/historical/json-rpc-over-http.html
 */

static std::map<int, std::string> gJsonRpcErrorStrings;

bool Round::RPC::JSON::HTTP::IsRequestMethod(const std::string &method) {
  if (method.compare(RPC::JSON::HTTP::METHOD) == 0)
    return true;
  if (method.compare(RPC::JSON::HTTP::GET_METHOD) == 0)
    return true;
  return false;
}

bool Round::RPC::JSON::HTTP::IsRequestPath(const std::string &method) {
  if (method.find(RPC::JSON::HTTP::ENDPOINT) == 0)
    return true;
  return false;
}

bool Round::RPC::JSON::HTTP::IsNoneEncorded(const std::string &value) {
  if (value.compare(RPC::JSON::HTTP::ENCORD_NONE) == 0)
    return true;
  return false;
}

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
    case RPC::JSON::ErrorCodeBadDestination :
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
    gJsonRpcErrorStrings[ErrorCodeUnknown]        = ROUNDCC_RPC_ERROR_CODE_UNKNOWN_MSG;
    gJsonRpcErrorStrings[ErrorCodeParserError]    = ROUNDCC_RPC_ERROR_CODE_PARSER_ERROR_MSG;
    gJsonRpcErrorStrings[ErrorCodeInvalidRequest] = ROUNDCC_RPC_ERROR_CODE_INVALID_REQUEST_MSG;
    gJsonRpcErrorStrings[ErrorCodeMethodNotFound] = ROUNDCC_RPC_ERROR_CODE_METHOD_NOT_FOUND_MSG;
    gJsonRpcErrorStrings[ErrorCodeInvalidParams]  = ROUNDCC_RPC_ERROR_CODE_INVALID_PARAMS_MSG;
    gJsonRpcErrorStrings[ErrorCodeInternalError]  = ROUNDCC_RPC_ERROR_CODE_INTERNAL_ERROR_MSG;
    
    gJsonRpcErrorStrings[ErrorCodeBadDestination]       = ROUNDCC_RPC_ERROR_CODE_BAD_DESTINATION_MSG;
    gJsonRpcErrorStrings[ErrorCodeMovedPermanently]     = ROUNDCC_RPC_ERROR_CODE_MOVED_PERMANENTLY_MSG;
    
    gJsonRpcErrorStrings[ErrorCodeScriptEngineInternalError]  = ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR_MSG;
    gJsonRpcErrorStrings[ErrorCodeScriptEngineNotFound]       = ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND_MSG;
    gJsonRpcErrorStrings[ErrorCodeScriptCompileError]         = ROUNDCC_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR_MSG;
    gJsonRpcErrorStrings[ErrorCodeScriptRuntimeError]         = ROUNDCC_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR_MSG;
  }

  if (gJsonRpcErrorStrings.find(jsonErrorCode) == gJsonRpcErrorStrings.end()) {
    if (IsServerErrorCode(jsonErrorCode)) {
      jsonErrorCode = ErrorCodeInternalError;
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

ssize_t Round::RPC::JSON::Encode(const byte *inBytes, size_t rawByteLen, std::string *encodedStr) {
  std::string base64Str;
  Base64::Encode(inBytes, rawByteLen, &base64Str);
  return URL::Encode(base64Str, encodedStr);
}

ssize_t Round::RPC::JSON::Decode(const std::string &encodedStr, byte **decordedBytes) {
  std::string decordedStr;
  URL::Decode(encodedStr, &decordedStr);
  return Base64::Decode(decordedStr, decordedBytes);
}
