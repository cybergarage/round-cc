/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/core/JSONRequest.h>

Round::JSONRequest::JSONRequest() {
}

Round::JSONRequest::~JSONRequest() {
}

bool Round::JSONRequest::setContent(const JSONObject *jsonObject) {
  if (!jsonObject)
    return false;
  
  std::string jsonString;
  jsonObject->toJSONString(&jsonString);
  if (jsonString.length() <= 0)
    return false;

  HTTPRequest::setContent(jsonString);

  return true;
}

bool Round::JSONRequest::setContent(const JSONObject &jsonObject) {
  return setContent(&jsonObject);
}
