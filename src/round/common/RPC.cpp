/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/RPC.h>
#include <uhttp/HTTP.h>

/*
 * JSON-RPC over HTTP
 * http://jsonrpc.org/historical/json-rpc-over-http.html
 */

int Round::RPC::JSON::HTTP::JSONDetailStatus2HTTPStatus(int jsonDetailStatus) {
  switch (jsonDetailStatus) {
    case RPC::JSON::DetailStatusParserError :
    case RPC::JSON::DetailStatusInvalidParams :
    case RPC::JSON::DetailStatusInternalError :
      return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
    case RPC::JSON::DetailStatusInvalidRequest :
      return uHTTP::HTTP::BAD_REQUEST;
    case RPC::JSON::DetailStatusMethodNotFound :
      return uHTTP::HTTP::NOT_FOUND;
  }
  
  if ((RPC::JSON::DetailStatusSpecificErrorMin <= jsonDetailStatus) && (jsonDetailStatus <=RPC::JSON::DetailStatusSpecificErrorMax)) {
    return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
  }
  
  return uHTTP::HTTP::INTERNAL_SERVER_ERROR;
}
