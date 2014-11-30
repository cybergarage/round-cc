/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/ServerNode.h>
#include <round/core/HTTP.h>
#include <round/core/impl/UPnPServerNode.h>
#include <round/common/StringTokenizer.h>
#include <round/core/Log.h>

const std::string Round::ServerNode::HTTP_JSON_RPC_ENTRYPOINT  = "/rpc/do";
const std::string Round::ServerNode::HTTP_JSON_RPC_CONTENTTYPE = "application/json-rpc";

Round::ServerNode::ServerNode() {
}

Round::ServerNode::~ServerNode() {
}

bool Round::ServerNode::getVersion(std::string *buffer, Error *error) const {
  *buffer = VER.c_str();
  return true;
}

bool Round::ServerNode::start(Error *error) {
  if (LocalNode::start(error) == false)
    return false;

  return true;
}

bool Round::ServerNode::stop(Error *error) {
  bool isSuccess = true;

  if (LocalNode::stop(error) == false)
    isSuccess = false;

  return isSuccess;
}

Round::HttpStatusCode Round::ServerNode::postJSONResponse(uHTTP::HTTPRequest *httpReq, const JSONObject &jsonObject) {
  std::string jsonString;
  jsonObject.toJSONString(&jsonString);

  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(uHTTP::HTTP::OK_REQUEST);
  httpRes.setContent(jsonString);
  return httpReq->post(&httpRes);
}

Round::HttpStatusCode Round::ServerNode::httpBadRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(uHTTP::HTTP::BAD_REQUEST);
  return httpReq->post(&httpRes);
}

Round::HttpStatusCode Round::ServerNode::httpNotFoundRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(uHTTP::HTTP::NOT_FOUND);
  return httpReq->post(&httpRes);
}

Round::HttpStatusCode  Round::ServerNode::httpInternaServerErrorOccured(uHTTP::HTTPRequest *httpReq) {
  uHTTP::HTTPResponse httpRes;
  httpRes.setStatusCode(uHTTP::HTTP::INTERNAL_SERVER_ERROR);
  return httpReq->post(&httpRes);
}

Round::HttpStatusCode Round::ServerNode::httpRootRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  JSONDictionary jsonDict;
  Error err;
  
  jsonDict.set(HTTP::JSONParam::VER, Node::VER);
  
  Cluster cluster;
  if (getCluster(&cluster, &err)) {
    jsonDict.set(HTTP::JSONParam::CLUSTER, cluster.getName());
  }

  std::string nodeName;
  if (getName(&nodeName, &err)) {
    jsonDict.set(HTTP::JSONParam::NAME, nodeName);
  }
  
  return postJSONResponse(httpReq, jsonDict);
}

Round::HttpStatusCode Round::ServerNode::httpGetRequestDictionaries(uHTTP::HTTPRequest *httpReq, JSONDictionary *dataDict, JSONDictionary *optionDict) {
  std::string httpContent = httpReq->getContent();
  if (httpContent.length() <= 0)
    return uHTTP::HTTP::BAD_REQUEST;

  JSONParser jsonParser;
  if (jsonParser.parse(httpContent) == false)
    return uHTTP::HTTP::BAD_REQUEST;

  std::string jsonString;

  if (jsonParser.getObject()->isDictionary() == false)
    return uHTTP::HTTP::BAD_REQUEST;

  JSONDictionary *reqDict = static_cast<JSONDictionary *>(jsonParser.getObject());
  if (!reqDict)
    return uHTTP::HTTP::BAD_REQUEST;

  for (JSONDictionary::iterator dict = reqDict->begin(); dict != reqDict->end(); dict++) {
    JSONObject *newValueObj;
    dict->second->copy(&newValueObj);
    if (HTTP::JSONParam::IsDataParameter(dict->first))
      dataDict->set(dict->first, newValueObj);
    else
      optionDict->set(dict->first, newValueObj);
  }

  return uHTTP::HTTP::OK_REQUEST;
}

Round::HttpStatusCode Round::ServerNode::httpDatabaseRequestRecieved(uHTTP::HTTPRequest *httpReq, const std::string &method, const std::string &uri) {
  return 0;
}

Round::HttpStatusCode Round::ServerNode::httpStatusRequestRecieved(uHTTP::HTTPRequest *httpReq, const std::string &uri) {
  Error error;
  
  /*
  if (uri.find(HTTP::URI::STATUS_NODE) == 0) {
    NodeStatus nodeStatus;
    nodeStatus.setState(getState());
    JSONResponseDictionary jsonDict;
    jsonDict.setNodeStatusResponse(nodeStatus);
    return postJSONResponse(httpReq, jsonDict);
  }

  if (uri.find(HTTP::URI::STATUS_NODEGRAPH) == 0) {
    JSONResponseArray jsonArray;
    jsonArray.setNodeGraphResponse(getNodeGraph());
    return postJSONResponse(httpReq, jsonArray);
  }
   */
  
  return uHTTP::HTTP::BAD_REQUEST;
}

bool Round::ServerNode::isNodeRpcRequest(const std::string &method, const std::string &uri) {
  if (method.compare("PUT") == 0) {
    if (uri.compare(HTTP_JSON_RPC_ENTRYPOINT) == 0)
      return true;
  }
  return false;
}

bool Round::ServerNode::isNodeHttpRequest(const std::string &method, const std::string &uri) {
  if (isNodeRootHttpRequest(method, uri))
    return true;
  if (isNodeDocumentRequest(method, uri))
    return true;
  if (isNodeStatusHttpRequest(method, uri))
    return true;
  return false;
}

bool Round::ServerNode::isNodeRootHttpRequest(const std::string &method, const std::string &uri) {
  if (method.compare("GET") == 0) {
    if (uri.compare("/") == 0)
      return true;
  }
  return false;
}

bool Round::ServerNode::isNodeDocumentRequest(const std::string &method, const std::string &uri) {
  if (uri.find(HTTP::URI::DOCUMENT) == 0)
    return true;
  return false;
}

bool Round::ServerNode::isNodeStatusHttpRequest(const std::string &method, const std::string &uri) {
  if (method.compare("GET") == 0) {
    if (uri.find(HTTP::URI::STATUS) == 0)
      return true;
  }
  return false;
}

Round::HttpStatusCode Round::ServerNode::httpRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  std::string method;
  httpReq->getMethod(method);
  std::string uri;
  httpReq->getURI(uri);

  HttpStatusCode statusCode = uHTTP::HTTP::BAD_REQUEST;
  if (isNodeDocumentRequest(method, uri)) {
    statusCode = httpDatabaseRequestRecieved(httpReq, method, uri);
  }
  else if (isNodeRootHttpRequest(method, uri)) {
    statusCode = httpRootRequestRecieved(httpReq);
  }
  else if (isNodeStatusHttpRequest(method, uri)) {
    statusCode = httpStatusRequestRecieved(httpReq, uri);
  }

  RoundLogInfo("%s %s %d %s:%d",
            method.c_str(),
            uri.c_str(),
            statusCode,
            httpReq->getLocalAddress(),
            httpReq->getLocalPort());

  return statusCode;
}
