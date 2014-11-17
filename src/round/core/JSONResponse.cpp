/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/core/JSONResponse.h>

Round::JSONResponse::JSONResponse() {
}

Round::JSONResponse::~JSONResponse() {
}

void Round::JSONResponse::setContent(const JSONObject &jsonObject) {
  std::string jsonString;
  jsonObject.toJSONString(&jsonString);
  HTTPResponse::setContent(jsonString);
}

bool Round::JSONResponse::getJSONObject(JSONObject **jsonObject) {
  std::string content = getContent();

  if (content.length() <= 0)
    return false;

  JSONResponseParser jsonParser;
  if (jsonParser.parse(content, jsonObject) == false)
    return false;

  return true;
}
