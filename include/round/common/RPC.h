/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_RPC_H_
#define _ROUNDCC_RPC_H_

#include <round/common/Error.h>
#include <round/common/Message.h>

#include <uhttp/HTTP.h>

namespace Round {

namespace RPC {

namespace HTTP {
static const std::string ENDPOINT     = "/rpc/do";
static const std::string CONTENT_TYPE = "application/json-rpc";
static const std::string METHOD       = "POST";
static const std::string ACCEPT       = CONTENT_TYPE;
}
  
namespace JSON {

static const std::string VERSION     = "2.0";

enum {
  ErrorCodeUnknown        = 0,
  ErrorCodeParserError    = -32700,
  ErrorCodeInvalidRequest = -32600,
  ErrorCodeMethodNotFound = -32601,
  ErrorCodeInvalidParams  = -32602,
  ErrorCodeInternalError  = -32603,
  ErrorCodeServerErrorMax = -32000,
  ErrorCodeServerErrorMin = -32099,
  ErrorCodeServerError    = ErrorCodeServerErrorMax,
};

const std::string &ErrorCodeToString(int jsonErrorCode);
bool IsServerErrorCode(int jsonErrorCode);

namespace HTTP {
  int ErrorCodeToHTTPStatusCode(int jsonErrorCode);
}

void ErrorCodeToError(int jsonErrorCode, Error *error);
  
class Message : public ::Round::Message {
 public:
  static const std::string JSON_RPC;
  static const std::string METHOD;
  static const std::string PARAMS;
  static const std::string TIMESTAMP;
  static const std::string ID;
  static const std::string RESULT;
  static const std::string ERROR;
  static const std::string CODE;
  static const std::string MESSAGE;
  
 public:
  Message();
  virtual ~Message();

  bool setVersion(const std::string &value) {
    return set(JSON_RPC, value);
  }

  bool getVersion(std::string *value) const {
    return get(JSON_RPC, value);
  }

  bool setId(size_t value) {
    return set(ID, value);
  }
  
  bool getId(size_t *value) const {
    return get(ID, value);
  }
  
  // Round Extention Methods.
  
  bool setTimestamp(clock_t value) {
    return set(TIMESTAMP, value);
  }
  
  bool getTimestamp(clock_t *value) const {
    return get(TIMESTAMP, value);
  }
};

class Request : public Message {
 public:
  Request();
  virtual ~Request();

  bool isValid();
  bool isNotify();

  bool setMethod(const std::string &value) {
    return set(METHOD, value);
  }
  
  bool getMethod(std::string *value) const {
    return get(METHOD, value);
  }
  
  bool hasMethod() const {return hasKey(METHOD);}
  bool isMethod(const std::string &method) const;
  
  bool setParams(const std::string &value) {
    return set(PARAMS, value);
  }
  
  bool getParams(std::string *value) const {
    return get(PARAMS, value);
  }
  
  void toHTTPRequest(uHTTP::HTTPRequest *httpReq) const;
};

class Response : public Message {
 public:
  Response();
  virtual ~Response();
    
  bool isValid();
  
  bool setResult(const std::string &value) {
    return set(RESULT, value);
  }
  
  bool getResult(std::string *value) const {
    return get(RESULT, value);
  }
  
  JSONDictionary *getResultDict();
  
  bool setResult(const std::string &key, const std::string &value);
  bool getResult(const std::string &key, std::string *value);
  bool setResult(const std::string &key, int value);
  bool getResult(const std::string &key, int *value);
  
  // NOTE : RPC error message uses only detail code and message in error object.
  bool setError(const Error *error);
  bool getError(Error *error) const;
  
  void toHTTPResponse(uHTTP::HTTPResponse *httpRes) const;
};

}
  
}
  
}

#endif
