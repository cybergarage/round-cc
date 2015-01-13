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
#include <round/common/HashObject.h>

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

static const std::string VER = "2.0";

enum {
  ErrorCodeUnknown                   = 0,
  ErrorCodeParserError               = -32700,
  ErrorCodeInvalidRequest            = -32600,
  ErrorCodeMethodNotFound            = -32601,
  ErrorCodeInvalidParams             = -32602,
  ErrorCodeInternalError             = -32603,
  
  ErrorCodeBadHashCode               = -32000,
  ErrorCodeMovedPermanently          = -32001,
  
  ErrorConditionFailed               = -32010,
  
  ErrorCodeScriptEngineInternalError = -32020,
  ErrorCodeScriptEngineNotFound      = -32021,
  ErrorCodeScriptCompileError        = -32022,
  ErrorCodeScriptRuntimeError        = -32023,
  
  ErrorCodeServerErrorMax            = -32000,
  ErrorCodeServerErrorMin            = -32099,
  ErrorCodeServerError               = ErrorCodeServerErrorMax,
};

const std::string &ErrorCodeToString(int jsonErrorCode);
bool IsServerErrorCode(int jsonErrorCode);

namespace HTTP {
  int ErrorCodeToHTTPStatusCode(int jsonErrorCode);
}

void ErrorCodeToError(int jsonErrorCode, Error *error);
  
class Message : public ::Round::Request {
 public:
  static const std::string JSON_RPC;
  static const std::string METHOD;
  static const std::string PARAMS;
  static const std::string ID;
  static const std::string RESULT;

  static const std::string ERROR;
  static const std::string CODE;
  static const std::string MESSAGE;
  
  static const std::string TIMESTAMP;
  static const std::string HASH;
  static const std::string DEST;
  static const std::string DEST_ONE;
  static const std::string DEST_ALL;
  
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

  // timestamp
  
  bool setTimestamp(clock_t value) {
    return set(TIMESTAMP, value);
  }
  
  bool getTimestamp(clock_t *value) const {
    return get(TIMESTAMP, value);
  }

  bool hasTimestamp() const {
    return hasKey(TIMESTAMP);
  }
  
  // hash
  
  bool setHash(const std::string &value) {
    return set(HASH, value);
  }
  
  bool setHash(HashObject *hashObj);
  
  bool getHash(std::string *value) const {
    return get(HASH, value);
  }
  
  bool hasHash() const {
    return hasKey(HASH);
  }

  // dest
  
  bool setDest(const std::string &value) {
    return set(DEST, value);
  }
  
  bool setDest(size_t value) {
    return set(DEST, value);
  }

  bool getDest(std::string *value) const {
    return get(DEST, value);
  }
  
  bool hasDest() const {
    return hasKey(DEST);
  }

  bool isDestValid() const;
  
  bool isDestOne() const;
  bool isDestAll() const;
  bool isDestQuorum() const;

  bool getQuorum(size_t *value) const;
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

class BatchRequest : public ::Round::BatchRequest {
    
 public:
    
  BatchRequest();
  ~BatchRequest();
};

class Response : public Message {
 public:
  Response();
  virtual ~Response();
    
  bool isValid();
  
  bool setResult(const std::string &value) {
    return set(RESULT, value);
  }
  
  bool setResult(JSONObject *value) {
    return set(RESULT, value);
  }

  bool getResult(std::string *value) const {
    return get(RESULT, value);
  }

  bool isBatchResult();
  JSONArray *getResultArray();
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
