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

Round::NodeRequest::NodeRequest() {
  init();
}

Round::NodeRequest::NodeRequest(const std::string &method) {
  init();
  setMethod(method);
}

void Round::NodeRequest::init() {
  this->httpReq = NULL;
}

Round::NodeRequest::~NodeRequest() {
  close();
}

bool Round::NodeRequest::close() {
  if (!this->httpReq)
    return false;
  
  delete this->httpReq;
  this->httpReq = NULL;

  return true;
}

void Round::NodeRequest::setSourceNodeParameters(const Node *node) {
  clock_t localTs = node->getLocalClock();
  setId(localTs);
  setTimestamp(localTs);
}

bool Round::NodeRequest::setHttpRequest(uHTTP::HTTPRequest *httpReq) {
  close();
  
  this->httpReq = httpReq;

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

  // hash
  
  if (httpReq->getParameterValue(RPC::JSON::Message::HASH, &value)) {
    nodeReq->setHash(value);
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
