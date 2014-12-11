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

const std::string Round::RPC::JSON::Message::VERSION = "2.0";
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
  set(JSON_RPC, VERSION);
}

Round::RPC::JSON::Message::~Message() {
}

bool Round::RPC::JSON::Message::setError(const Error &error) {
  JSONDictionary *errorDict = new JSONDictionary();
  if (!errorDict)
    return false;
  errorDict->set(CODE, error.getCode());
  errorDict->set(MESSAGE, error.getMessage());
  
  return set(ERROR, errorDict);
}

bool Round::RPC::JSON::Message::getError(Error *error) {
  if (!error)
    return false;
  
  JSONObject *errorObj;
  if (!get(ERROR, &errorObj))
    return false;
  JSONDictionary *errorDict = dynamic_cast<JSONDictionary *>(errorObj);
  if (!errorDict)
    return false;
  
  int errorCode;
  if (!errorDict->get(CODE, &errorCode))
    return false;
  error->setCode(errorCode);
  
  std::string errorMsg;
  if (!errorDict->get(MESSAGE, &errorMsg))
    return false;
  error->setMessage(errorMsg);
  
  return true;
}
