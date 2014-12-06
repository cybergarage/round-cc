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

namespace JSON {

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
  int ErrorCodeToHTTPStatus(int jsonErrorCode);
}

class Message : public ::Round::Message {
 public:
  static const std::string VERSION;
  
  static const std::string JSON_RPC;
  static const std::string METHOD;
  static const std::string PARAMS;
  static const std::string ID;
  static const std::string RESULT;
  static const std::string ERROR;
  static const std::string CODE;
  static const std::string MESSAGE;
  
 public:
  Message();
  virtual ~Message();

  bool getVersion(std::string *value) const {
    return get(JSON_RPC, value);
  }

  bool setMethod(const std::string &value) {
    return set(METHOD, value);
  }
  
  bool getMethod(std::string *value) const {
    return get(METHOD, value);
  }

  bool setParams(const std::string &value) {
    return set(PARAMS, value);
  }
  
  bool getParams(std::string *value) const {
    return get(PARAMS, value);
  }

  bool setResult(const std::string &value) {
    return set(RESULT, value);
  }
  
  bool getResult(std::string *value) const {
    return get(RESULT, value);
  }
  
  bool setId(const std::string &value) {
    return set(ID, value);
  }
  
  bool getId(std::string *value) const {
    return get(ID, value);
  }
  
  bool setError(const Error &error);
  bool getError(Error *error);

};

class Request : public Message {
 public:
  Request();
  virtual ~Request();

  bool isValid();
  bool isNotify();

  bool hasMethod() const {return hasKey(METHOD);}
  bool isMethod(const std::string &method) const;
};

class Response : public Message {
 public:
  Response();
  virtual ~Response();
    
  bool isValid();
  
  void toHTTPResponse(uHTTP::HTTPResponse *httpRes) const;
};

}
  
}
  
}

#endif
