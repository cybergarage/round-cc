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

const std::string Round::RPC::JSON::Message::JSON_RPC = "jsonrpc";
const std::string Round::RPC::JSON::Message::METHOD = "method";
const std::string Round::RPC::JSON::Message::PARAMS = "params";
const std::string Round::RPC::JSON::Message::ID = "id";
const std::string Round::RPC::JSON::Message::ERROR = "error";
const std::string Round::RPC::JSON::Message::CODE = "code";
const std::string Round::RPC::JSON::Message::MESSAGE = "message";
const std::string Round::RPC::JSON::Message::RESULT = "result";

const std::string Round::RPC::JSON::Message::TIMESTAMP = "ts";

Round::RPC::JSON::Message::Message() {
}

Round::RPC::JSON::Message::~Message() {
}

bool Round::RPC::JSON::Message::setError(const Error *error) {
  if (!error)
    return false;
  
  JSONDictionary *errorDict = NULL;
  JSONObject *errorObj;
  if (get(ERROR, &errorObj)) {
    errorDict = dynamic_cast<JSONDictionary *>(errorObj);
  }
  
  if (!errorDict) {
    errorDict = new JSONDictionary();
    if (!set(ERROR, errorDict)) {
      delete errorDict;
      return false;
    }
  }
  
  errorDict->set(CODE, error->getDetailCode());
  errorDict->set(MESSAGE, error->getDetailMessage());
  
  return true;
}

bool Round::RPC::JSON::Message::getError(Error *error) const {
  if (!error)
    return false;
  
  JSONObject *errorObj;
  if (!get(ERROR, &errorObj))
    return false;
  JSONDictionary *errorDict = dynamic_cast<JSONDictionary *>(errorObj);
  if (!errorDict)
    return false;
  
  int errorCode;
  if (errorDict->get(CODE, &errorCode)) {
    error->setDetailCode(errorCode);
  }

  std::string errorMsg;
  if (errorDict->get(MESSAGE, &errorMsg)) {
    error->setDetailMessage(errorMsg);
  }
  
  return true;
}
