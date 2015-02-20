/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_RPC_H_
#define _ROUNDCC_RPC_H_

#include <round/common/types.h>
#include <round/common/Error.h>
#include <round/common/Message.h>
#include <round/common/HashObject.h>

#include <uhttp/HTTP.h>

namespace Round {

namespace RPC {

namespace JSON {

static const std::string VER = "2.0";

enum {
  ErrorCodeUnknown                   = 0,
  ErrorCodeParserError               = -32700,
  ErrorCodeInvalidRequest            = -32600,
  ErrorCodeMethodNotFound            = -32601,
  ErrorCodeInvalidParams             = -32602,
  ErrorCodeInternalError             = -32603,
  
  ErrorCodeBadDestination            = -32000,
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
void ErrorCodeToError(int jsonErrorCode, Error *error);

namespace HTTP {
  static const std::string ENDPOINT     = "/rpc";
  static const std::string CONTENT_TYPE = "application/json";
  static const std::string METHOD       = uHTTP::HTTP::POST;
  static const std::string GET_METHOD   = uHTTP::HTTP::GET;
  static const std::string ACCEPT       = CONTENT_TYPE;
  static const std::string ENCORD       = "encode";
  static const std::string ENCORD_NONE  = "none";
  bool IsRequestMethod(const std::string &method);
  bool IsRequestPath(const std::string &method);
  bool IsNoneEncorded(const std::string &value);
  int ErrorCodeToHTTPStatusCode(int jsonErrorCode);
}

ssize_t Encode(const byte *inBytes, size_t rawByteLen, std::string *encodedStr);
ssize_t Decode(const std::string &encodedStr, byte **decordedBytes);

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
  static const std::string DEST;
  static const std::string DEST_ANY;
  static const std::string DEST_ALL;
  static const std::string TYPE;
  static const std::string COND;
  static const std::string DIGEST;
  static const std::string QUORUM;
  
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
  
  bool setId(const std::string &value) {
    return set(ID, value);
  }
  
  bool getId(size_t *value) const {
    return get(ID, value);
  }
  
  bool getId(const std::string *value) const {
    return get(ID, value);
  }
  
  // Round Extention Methods.

  // timestamp
  
  bool setTimestamp(clock_t value) {
    return set(TIMESTAMP, value);
  }
  
  bool setTimestamp(const std::string &value) {
    return set(TIMESTAMP, value);
  }
  
  bool getTimestamp(clock_t *value) const {
    return get(TIMESTAMP, value);
  }

  bool getTimestamp(const std::string *value) const {
    return get(TIMESTAMP, value);
  }
  
  bool hasTimestamp() const {
    return hasKey(TIMESTAMP);
  }
  
  // dest
  
  bool setDest(const std::string &value) {
    return set(DEST, value);
  }
  
  bool setDest(HashObject *hashObj);
  
  bool getDest(std::string *value) const {
    return get(DEST, value);
  }
  
  bool hasDest() const {
    return hasKey(DEST);
  }

  bool isDestValid() const;
  bool isDestAny() const;
  bool isDestAll() const;
  bool isDestHash() const;
  bool isDestOne() const;

  // quorum
  
  bool setQuorum(size_t value) {
    return set(QUORUM, value);
  }
  
  bool setQuorum(const std::string &value) {
    return set(QUORUM, value);
  }
  
  bool getQuorum(size_t *value) const {
    return get(QUORUM, value);
  }
  
  bool hasQuorum() const {
    return hasKey(QUORUM);
  }
  
  
 // type
  
  bool setType(const std::string &value) {
    return set(TYPE, value);
  }
  
  bool getType(std::string *value) const {
    return get(TYPE, value);
  }

  bool hasType() const {
    return hasKey(TYPE);
  }

  // cond
  
  bool setCond(const std::string &value) {
    return set(COND, value);
  }
  
  bool getCond(std::string *value) const {
    return get(COND, value);
  }
  
  bool hasCond() const {
    return hasKey(COND);
  }

  // digest
  
  bool setDigest(const std::string &value) {
    return set(DIGEST, value);
  }
  
  bool getDigest(std::string *value) const {
    return get(DIGEST, value);
  }
  
  bool hasDigest() const {
    return hasKey(DIGEST);
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
  
  bool hasParams() const {
    return hasKey(PARAMS);
  }
  
  void toHTTPPostRequest(uHTTP::HTTPRequest *httpReq) const;
  void toHTTPGetRequest(uHTTP::HTTPRequest *httpReq, bool jsonRpcEncodeEnable) const;
};

class BatchRequest : public ::Round::BatchRequest {
    
 public:
    
  BatchRequest();
  ~BatchRequest();

  void toHTTPPostRequest(uHTTP::HTTPRequest *httpReq) const;
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

class BatchResponse : public JSONArray {
    
public:
  BatchResponse();
  virtual ~BatchResponse();

  void toHTTPResponse(uHTTP::HTTPResponse *httpRes) const;
};

class Parser : public JSONParser {
    
  public:
    
  Parser();
  virtual ~Parser();
  
  virtual JSONDictionary *createJSONDictionary() {
    return new RPC::JSON::Request();
  }
    
  virtual JSONArray *createJSONArray() {
    return new RPC::JSON::BatchRequest();
  }
};
  
  
}
  
}
  
}

#endif
