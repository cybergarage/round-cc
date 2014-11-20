/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Log.h>
#include <round/core/RemoteNode.h>
#include <round/core/NodeGraph.h>

#include <uhttp/net/Socket.h>

Round::RemoteNode::RemoteNode(const Round::Node *node) {
  this->requestAddress = node->getRequestAddress();
  this->requestPort = node->getRequestPort();
}

Round::RemoteNode::RemoteNode(const std::string &address, int port) {
  this->requestAddress = address;
  this->requestPort = port;
}

Round::RemoteNode::~RemoteNode() {
}

void Round::RemoteNode::setJSONResponseError(Error *error) const {
  if (!error)
    return;

  int statusCode = uHTTP::HTTP::NOT_FOUND;
  error->setCode(statusCode);
  error->setMessage(uHTTP::HTTP::StatusCode2String(statusCode));
}

int Round::RemoteNode::postJSONRequest(const std::string &method, const std::string &uri, const JSONObject *jsonContent, JSONObject **jsonResObject, Error *error) const {
  JSONRequest jsonReq;
  jsonReq.setMethod(method);
  jsonReq.setURI(uri);
  jsonReq.setHost(getRequestAddress(), getRequestPort());
  jsonReq.setContent(jsonContent);

  JSONResponse jsonResponse;
  jsonReq.post(getRequestAddress(), getRequestPort(), &jsonResponse);

  int statusCode = jsonResponse.getStatusCode();

  if (statusCode == uHTTP::HTTP::OK_REQUEST) {
    if (jsonResponse.getJSONObject(jsonResObject) == true) {
      if (!jsonResObject) {
        setJSONResponseError(error);
        statusCode = error->getCode();
      }
    }
  }
  else {
    if (error) {
      error->setCode(statusCode);
      error->setMessage(uHTTP::HTTP::StatusCode2String(statusCode));
    }
  }

  return statusCode;
}

bool Round::RemoteNode::postMessage(const NodeRequest &reqMsg, NodeResponse *resMsg) {
  return false;
}

Round::Node *Round::RemoteNode::clone() const {
  return new RemoteNode(this);
}
