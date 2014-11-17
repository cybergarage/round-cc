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

bool Round::RemoteNode::getCluster(Cluster *cluster, Error *error) const {
  JSONObject *jsonResponse = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::CLUSTER, NULL, &jsonResponse, error);
  
  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;
  
  bool isSuccess = true;
  
  if (jsonResponse->isDictionary()) {
    JSONDictionary *jsonDir = dynamic_cast<JSONDictionary *>(jsonResponse);
    std::string clusterName;
    if (jsonDir->get(HTTP::JSONParam::CLUSTER, &clusterName) == false) {
      setJSONResponseError(error);
      isSuccess = false;
    }
    cluster->setName(clusterName);
  }
  else {
    setJSONResponseError(error);
    isSuccess = false;
  }
  
  delete jsonResponse;
  
  return isSuccess;
}

bool Round::RemoteNode::getName(std::string *buffer, Error *error) const {
  JSONObject *jsonResponse = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::NAME, NULL, &jsonResponse, error);
  
  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;
  
  bool isSuccess = true;
  
  if (jsonResponse->isDictionary()) {
    JSONDictionary *jsonDir = dynamic_cast<JSONDictionary *>(jsonResponse);
    if (jsonDir->get(HTTP::JSONParam::NAME, buffer) == false) {
      setJSONResponseError(error);
      isSuccess = false;
    }
  }
  else {
    setJSONResponseError(error);
    isSuccess = false;
  }
  
  delete jsonResponse;
  
  return isSuccess;
}

bool Round::RemoteNode::getVersion(std::string *buffer, Error *error) const {
  JSONObject *jsonResponse = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::VER, NULL, &jsonResponse, error);

  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;

  bool isSuccess = true;

  if (jsonResponse->isDictionary()) {
    JSONDictionary *jsonDir = dynamic_cast<JSONDictionary *>(jsonResponse);
    if (jsonDir->get(HTTP::JSONParam::VER, buffer) == false) {
      setJSONResponseError(error);
      isSuccess = false;
    }
  }
  else {
    setJSONResponseError(error);
    isSuccess = false;
  }
  
  delete jsonResponse;

  return isSuccess;
}

bool Round::RemoteNode::getStatus(NodeStatus *nodeStatus, Error *error) const {
  JSONObject *jsonResObj = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::STATUS_NODE, NULL, &jsonResObj, error);

  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;

  bool isSuccess = true;

  nodeStatus->setState(NodeStatus::UNKNOWN);

  JSONResponseDictionary *jsonResDict = dynamic_cast<JSONResponseDictionary *>(jsonResObj);
  if (jsonResDict) {
    std::string jsonString;
    jsonResDict->getNodeStatusResponse(nodeStatus);
  }
  else {
    setJSONResponseError(error);
  }
  
  delete jsonResObj;

  return isSuccess;
}

bool Round::RemoteNode::getTabletSpaces(TabletSpaceList *tabletSpaceList, Error *error) {
JSONObject *jsonResponse = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::STATUS_DOCUMENTS, NULL, &jsonResponse, error);

  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;

  bool isSuccess = true;

  delete jsonResponse;

  return isSuccess;
}

bool Round::RemoteNode::getNodeGraph(NodeGraph *nodeGraph, Error *error) {
  JSONObject *jsonResponse = NULL;
  int statusCode = postJSONRequest(HTTP::GET, HTTP::URI::STATUS_NODEGRAPH, NULL, &jsonResponse, error);

  if (statusCode != uHTTP::HTTP::OK_REQUEST)
    return false;

  bool isSuccess = true;

  JSONResponseArray *jsonResArray = dynamic_cast<JSONResponseArray *>(jsonResponse);
  if (jsonResArray) {
    if (jsonResArray->getNodeGraphResponse(nodeGraph) == false) {
      setJSONResponseError(error);
      isSuccess = false;
    }
  }
  else {
    setJSONResponseError(error);
    isSuccess = false;
  }
  
  delete jsonResponse;

  return isSuccess;
}

bool Round::RemoteNode::postMessage(const Message *msg)  {
  return false;
}

Round::Node *Round::RemoteNode::clone() const {
  return new RemoteNode(this);
}
