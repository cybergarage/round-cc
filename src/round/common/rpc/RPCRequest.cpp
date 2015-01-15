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

Round::RPC::JSON::Request::Request() {
}

Round::RPC::JSON::Request::~Request() {
}

bool Round::RPC::JSON::Request::isValid() {
  if (!hasKey(JSON_RPC))
    return false;

  if (!hasKey(METHOD))
    return false;

  JSONObject *methodObj;
  if (!get(METHOD, &methodObj))
    return false;
  
  if (!methodObj->isString())
    return false;
  
  return true;
}

bool Round::RPC::JSON::Request::isNotify() {
  if (!isValid())
    return false;
  return !hasKey(ID);
}

bool Round::RPC::JSON::Request::isMethod(const std::string &method) const {
  std::string reqMethod;
  if (!get(METHOD, &reqMethod))
    return false;
  return (method.compare(reqMethod) == 0) ? true : false;
}

void Round::RPC::JSON::Request::toHTTPPostRequest(uHTTP::HTTPRequest *httpReq) const {
  if (!httpReq)
    return;
  
  httpReq->setMethod(RPC::JSON::HTTP::METHOD);
  httpReq->setURI(RPC::JSON::HTTP::ENDPOINT);
  httpReq->setContentType(RPC::JSON::HTTP::CONTENT_TYPE);
  
  std::string jsonString;
  toJSONString(&jsonString);
  httpReq->setContent(jsonString);
}

void Round::RPC::JSON::Request::toHTTPGetRequest(uHTTP::HTTPRequest *httpReq, bool jsonRpcEncodeEnable) const {
  if (!httpReq)
    return;
  
  httpReq->setMethod(RPC::JSON::HTTP::METHOD);
  httpReq->setContentType(RPC::JSON::HTTP::CONTENT_TYPE);

  std::stringstream uriBuf;
  std::string paramVal;
  
  uriBuf << RPC::JSON::HTTP::ENDPOINT;
  if (getMethod(&paramVal)) {
    uriBuf << "?" << RPC::JSON::Message::METHOD << "=" << paramVal;
    
    if (getParams(&paramVal)) {
      std::string encodedStr;
      if (jsonRpcEncodeEnable) {
        if (RPC::JSON::Encode((byte *)paramVal.c_str(), paramVal.length(), &encodedStr)) {
          uriBuf << "&" << RPC::JSON::Message::PARAMS << "=" << encodedStr;
        }
      }
      else {
        uriBuf << "&" << RPC::JSON::Message::PARAMS << "=" << paramVal;
      }
    }

    for (JSONDictionary::const_iterator jsonObjIt = begin(); jsonObjIt != end(); jsonObjIt++) {
      std::string key = jsonObjIt->first;
      if (key.compare(RPC::JSON::Message::METHOD) == 0)
        continue;
      if (key.compare(RPC::JSON::Message::PARAMS) == 0)
        continue;
      JSONObject *jsonObj = jsonObjIt->second;
      if (!jsonObj)
        continue;
      std::string jsonObjStr;
      if (!jsonObj->toJSONString(&jsonObjStr))
        continue;
      uriBuf << "&" << key << "=" << jsonObjStr;
    }
  }
  
  httpReq->setURI(uriBuf.str());
}
