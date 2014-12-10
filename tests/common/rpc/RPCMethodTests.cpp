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

#include <map>
#include <round/common/RPC.h>

using namespace Round;

static size_t GetJsonRpcAllErrorCodes(std::vector<int> &errorCodes) {
  errorCodes.push_back(RPC::JSON::ErrorCodeUnknown);
  errorCodes.push_back(RPC::JSON::ErrorCodeParserError);
  errorCodes.push_back(RPC::JSON::ErrorCodeInvalidRequest);
  errorCodes.push_back(RPC::JSON::ErrorCodeMethodNotFound);
  errorCodes.push_back(RPC::JSON::ErrorCodeInvalidParams);
  errorCodes.push_back(RPC::JSON::ErrorCodeServerErrorMax);
  errorCodes.push_back(RPC::JSON::ErrorCodeServerErrorMin);
  errorCodes.push_back(RPC::JSON::ErrorCodeServerError);
  
  return errorCodes.size();
}

BOOST_AUTO_TEST_CASE(RpcErrorCodeStringTest) {
  std::vector<int> errorCodes;
  size_t errorCodeCnt = GetJsonRpcAllErrorCodes(errorCodes);
  
  for (int n=0; n<errorCodeCnt; n++) {
    std::string errStr = RPC::JSON::ErrorCodeToString(errorCodes[n]);
    BOOST_CHECK(0 < errStr.length());
  }
}

BOOST_AUTO_TEST_CASE(RpcHttpStatusMethodTest) {
  std::vector<int> errorCodes;
  size_t errorCodeCnt = GetJsonRpcAllErrorCodes(errorCodes);
  
  for (int n=0; n<errorCodeCnt; n++) {
    int statusCode = RPC::JSON::HTTP::ErrorCodeToHTTPStatusCode(errorCodes[n]);
    BOOST_CHECK(0 < statusCode);
  }
}

BOOST_AUTO_TEST_CASE(RpcHttpServerErrorCodeTest) {
  BOOST_CHECK(RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeServerErrorMax));
  BOOST_CHECK(RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeServerErrorMin));
  BOOST_CHECK(RPC::JSON::IsServerErrorCode((RPC::JSON::ErrorCodeServerErrorMax + RPC::JSON::ErrorCodeServerErrorMax)/2));

  BOOST_CHECK(!RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeUnknown));
  BOOST_CHECK(!RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeParserError));
  BOOST_CHECK(!RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeInvalidRequest));
  BOOST_CHECK(!RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeMethodNotFound));
  BOOST_CHECK(!RPC::JSON::IsServerErrorCode(RPC::JSON::ErrorCodeInvalidParams));
}
