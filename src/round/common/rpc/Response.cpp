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

Round::RPC::JSON::Response::Response() {
}

Round::RPC::JSON::Response::~Response() {
}

bool Round::RPC::JSON::Response::isValid() {
  if (!hasKey(JSON_RPC))
    return false;
  
  if (hasKey(ERROR))
    return true;
  
  if (hasKey(RESULT))
    return true;
  
  return false;
}

Round::JSONDictionary *Round::RPC::JSON::Response::getResultDict() {
  JSONObject *jsonObj = NULL;
  get(RESULT, &jsonObj);
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (jsonDict)
    return jsonDict;
  
  jsonDict = new JSONDictionary();
  set(RESULT, jsonDict);
  
  return jsonDict;
}

bool Round::RPC::JSON::Response::setResult(const std::string &key, const std::string &value) {
  JSONDictionary *jsonDict = getResultDict();
  if (!jsonDict)
    return false;
  return jsonDict->set(key, value);
}

bool Round::RPC::JSON::Response::getResult(const std::string &key, std::string *value) {
  JSONDictionary *jsonDict = getResultDict();
  if (!jsonDict)
    return false;
  return jsonDict->get(key, value);
}

bool Round::RPC::JSON::Response::setResult(const std::string &key, int value) {
  JSONDictionary *jsonDict = getResultDict();
  if (!jsonDict)
    return false;
  return jsonDict->set(key, value);
}

bool Round::RPC::JSON::Response::getResult(const std::string &key, int *value) {
  JSONDictionary *jsonDict = getResultDict();
  if (!jsonDict)
    return false;
  return jsonDict->get(key, value);
}

bool Round::RPC::JSON::Response::setError(const Error *error) {
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

bool Round::RPC::JSON::Response::getError(Error *error) const {
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

void Round::RPC::JSON::Response::toHTTPResponse(uHTTP::HTTPResponse *httpRes) const {
  if (!httpRes)
    return;
  
  std::string resContent;
  toJSONString(&resContent);
  httpRes->setContent(resContent);
}
