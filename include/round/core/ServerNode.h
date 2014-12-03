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
  
  bool isNodeRpcRequest(const std::string &method, const std::string &uri);
  HttpStatusCode httpBadRpcRequestRecieved(uHTTP::HTTPRequest *httpReq, int rpcErrorCode);
  HttpStatusCode httpNodeRpcRequestReceived(uHTTP::HTTPRequest *httpReq);

private:
  
  int serverPort;
  std::string serverAddress;
};

}

#endif
