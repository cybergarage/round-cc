/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <iostream>
#include <round/core/HTTP.h>
#include <round/core/JSONResponse.h>

Round::JSONResponseDictionary::JSONResponseDictionary() {
}

Round::JSONResponseDictionary::~JSONResponseDictionary() {
}

bool Round::JSONResponseDictionary::setGetResponse(const std::string &value) {
  JSONParser jsonParser;
  if (jsonParser.parse(value) == false)
    return false;

  JSONObject *jsonObj = jsonParser.getObject();
  if (!jsonObj)
    return false;

  if (jsonObj->isDictionary() == false)
    return false;
  
  set(static_cast<JSONDictionary *>(jsonObj));

  return true;
}

bool Round::JSONResponseDictionary::getGetResponse(std::string *value) {
  toJSONString(value);
  return true;
}

bool Round::JSONResponseDictionary::setNodeStatusResponse(const NodeStatus &nodeStatus) {
  set(HTTP::JSONParam::STATUS, nodeStatus.getStateString());
  return true;
}

bool Round::JSONResponseDictionary::getNodeStatusResponse(NodeStatus *nodeStatus) {
  if (hasKey(HTTP::JSONParam::STATUS) == false)
    return false;
  
  JSONObject *jsonObj = NULL;
  if (!get(HTTP::JSONParam::STATUS, &jsonObj))
    return false;
  if (jsonObj->isString() == false)
    return false;
  
  JSONString *stateJson = dynamic_cast<JSONString *>(jsonObj);
  if (!stateJson)
    return false;
  
  nodeStatus->setState(*stateJson);
  
  return true;
}
