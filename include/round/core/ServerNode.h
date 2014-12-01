/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODESERVER_H_
#define _ROUNDCC_NODESERVER_H_

#include <uhttp/http/HTTPServer.h>

#include <round/core/LocalNode.h>

namespace Round {
      
typedef uHTTP::HTTP::StatusCode HttpStatusCode;

class ServerNode : public LocalNode {
public:
  static const std::string HTTP_JSON_RPC_ENTRYPOINT;
  static const std::string HTTP_JSON_RPC_CONTENTTYPE;
  
 public:
  ServerNode();
  virtual ~ServerNode();

  bool getVersion(std::string *buffer, Error *error) const;

  bool start(Error *error);
  bool stop(Error *error);

  int getRequestPort() const  {
    return this->serverPort;
  }
  
  const char *getRequestAddress() const {
    return this->serverAddress.c_str();
  }
  
protected:

  void setRequestAddress(const std::string &host) {
    this->serverAddress = host;
  }
  
  void setRequestPort(int port) {
    this->serverPort = port;
  }
  
  bool isNodeHttpRequest(const std::string &method, const std::string &uri);
  
  HttpStatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);
  HttpStatusCode httpBadRequestRecieved(uHTTP::HTTPRequest *httpReq);
  HttpStatusCode httpNotFoundRequestRecieved(uHTTP::HTTPRequest *httpReq);
  HttpStatusCode httpInternaServerErrorOccured(uHTTP::HTTPRequest *httpReq);

private:

  bool isNodeRpcRequest(const std::string &method, const std::string &uri);
  bool isNodeRootHttpRequest(const std::string &method, const std::string &uri);
  bool isNodeDocumentRequest(const std::string &method, const std::string &uri);
  bool isNodeStatusHttpRequest(const std::string &method, const std::string &uri);

  HttpStatusCode httpNodeRpcRequestReceived(uHTTP::HTTPRequest *httpReq);
  
  HttpStatusCode postJSONResponse(uHTTP::HTTPRequest *httpReq, const JSONObject &jsonObject);

  HttpStatusCode httpGetRequestDictionaries(uHTTP::HTTPRequest *httpReq, JSONDictionary *dataDict, JSONDictionary *optionDict);
  HttpStatusCode httpRootRequestRecieved(uHTTP::HTTPRequest *httpReq);
  HttpStatusCode httpStatusRequestRecieved(uHTTP::HTTPRequest *httpReq, const std::string &uri);
  HttpStatusCode httpDatabaseRequestRecieved(uHTTP::HTTPRequest *httpReq, const std::string &method, const std::string &uri);

private:
  
  int serverPort;
  std::string serverAddress;
};

}

#endif
