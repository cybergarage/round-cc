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

namespace Round {

namespace RPC {

namespace JSON {

enum {
  DetailStatusParserError          = -32700,
  DetailStatusInvalidRequest       = -32600,
  DetailStatusMethodNotFound       = -32601,
  DetailStatusInvalidParams        = -32602,
  DetailStatusInternalError        = -32603,
  DetailStatusSpecificErrorMax     = -32000,
  DetailStatusSpecificErrorMin     = -32099,
};

namespace HTTP {
  int JSONDetailStatus2HTTPStatus(int jsonDetailStatus);
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

}
  
}
  
}

#endif
