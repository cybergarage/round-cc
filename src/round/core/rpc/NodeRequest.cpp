/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <boost/algorithm/string/replace.hpp>

#include <round/core/NodeMessage.h>
#include <round/core/Node.h>
#include <round/common/encoding/URL.h>

const std::string Round::NodeRequest::SYNC = "sync";
const std::string Round::NodeRequest::ANY = "*";

Round::NodeRequest::NodeRequest() {
}

Round::NodeRequest::NodeRequest(const std::string &method) {
  setMethod(method);
}

Round::NodeRequest::NodeRequest(const NodeRequest *nodeReq) {
  JSONDictionary::set(nodeReq);
}

Round::NodeRequest::NodeRequest(const NodeRequest *nodeReq, const std::string &defaultParams) {
  setParamsWithDefault(nodeReq, defaultParams);
}

Round::NodeRequest::~NodeRequest() {
}

void Round::NodeRequest::setSourceNodeParameters(const Node *node) {
  clock_t localTs = node->getLocalClock();
  setId(localTs);
  setTimestamp(localTs);
}

bool Round::NodeRequest::setParamsWithDefault(const NodeRequest *nodeReq, const std::string &defaultParams) {
  JSONDictionary::set(nodeReq);

  // Request has no params (Use default params)
  
  std::string reqParams;
  if (!nodeReq->getParams(&reqParams)) {
    setParams(defaultParams);
    return true;
  }

  return setParamsWithDefault(reqParams, defaultParams);
}

bool Round::NodeRequest::setParamsWithDefault(const std::string &reqParams, const std::string &defaultParams) {

  // Request has no params (Use default params)
  
  if (reqParams.length() <= 0) {
    setParams(defaultParams);
    return true;
  }

  // Request or default is invalid JSON format. (Use request params)

  Error error;
  
  JSONParser reqParamsJsonParser;
  bool isReqJSONParams = reqParamsJsonParser.parse(reqParams, &error);
  
  JSONParser defaultParamsJsonParser;
  bool isDefaultJSONParams = defaultParamsJsonParser.parse(defaultParams, &error);
  
  if (!isReqJSONParams || !isDefaultJSONParams) {
    setParams(reqParams);
    return true;
  }
  
  // Request and default are JSONDictionary (Merge params)

  JSONDictionary *reqParamDict = dynamic_cast<JSONDictionary *>(reqParamsJsonParser.getRootObject());
  JSONDictionary *defaultParamDict = dynamic_cast<JSONDictionary *>(defaultParamsJsonParser.getRootObject());
  if (reqParamDict && defaultParamDict)  {
    JSONDictionary mergeDict;
    mergeDict.add(reqParamDict);
    mergeDict.add(defaultParamDict);
    std::string mergeParams;
    mergeDict.toJSONString(&mergeParams);
    setParams(mergeParams);
    return true;
  }
  
  // Request and default are JSONArray (Merge params)
  
  JSONArray *reqParamArray = dynamic_cast<JSONArray *>(reqParamsJsonParser.getRootObject());
  JSONArray *defaultParamArray = dynamic_cast<JSONArray *>(defaultParamsJsonParser.getRootObject());
  if (reqParamArray && defaultParamArray)  {
    JSONArray mergeArray;
    mergeArray.add(reqParamArray);
    mergeArray.add(defaultParamArray);
    std::string mergeParams;
    mergeArray.toJSONString(&mergeParams);
    setParams(mergeParams);
    return true;
  }
  
  // Request and default are not same data type (Use request params)
  
  setParams(reqParams);
  
  return true;
}

Round::NodeRequest *Round::NodeRequest::CreateFromHTTPGetRequest(uHTTP::HTTPRequest *httpReq) {
  if (!httpReq->isGetRequest())
    return NULL;

  NodeRequest *nodeReq = new NodeRequest();
  
  std::string value;

  // jsonrpc
  
  if (httpReq->getParameterValue(RPC::JSON::Message::JSON_RPC, &value)) {
    nodeReq->setVersion(value);
  }
  
  // method
  
  if (httpReq->getParameterValue(RPC::JSON::Message::METHOD, &value)) {
    nodeReq->setMethod(value);
  }
  
  // id
  
  if (httpReq->getParameterValue(RPC::JSON::Message::ID, &value)) {
    nodeReq->setId(value);
  }
  
  // timestamp
  
  if (httpReq->getParameterValue(RPC::JSON::Message::TIMESTAMP, &value)) {
    nodeReq->setTimestamp(value);
  }

  // quorum
  
  if (httpReq->getParameterValue(RPC::JSON::Message::QUORUM, &value)) {
    nodeReq->setQuorum(value);
  }
  
  // dest
  
  if (httpReq->getParameterValue(RPC::JSON::Message::DEST, &value)) {
    nodeReq->setDest(value);
  }
  
  // type
  
  if (httpReq->getParameterValue(RPC::JSON::Message::TYPE, &value)) {
    nodeReq->setType(value);
  }
  
  // digest
  
  if (httpReq->getParameterValue(RPC::JSON::Message::DIGEST, &value)) {
    nodeReq->setDigest(value);
  }

  // params
  
  if (httpReq->getParameterValue(RPC::JSON::Message::PARAMS, &value)) {
    bool isJsonRpcEncorded = true;
    std::string encord;
    if (httpReq->getParameterValue(RPC::JSON::HTTP::ENCORD, &encord)) {
      isJsonRpcEncorded = RPC::JSON::HTTP::IsNoneEncorded(encord) ? false : true;
    }
    if (isJsonRpcEncorded) {
      byte *decordedBytes = NULL;
      size_t decordedByteLen = RPC::JSON::Decode(value, &decordedBytes);
      if (decordedBytes) {
        std::string decordedString((const char *)decordedBytes, decordedByteLen);
        nodeReq->setParams(decordedString);
        free(decordedBytes);
      }
    }
    else {
      std::string decordedStr;
      URL::Decode(value, &decordedStr);
      nodeReq->setParams(decordedStr);
    }
  }

  return nodeReq;
}
