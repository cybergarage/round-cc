/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
  ServerNode();
  virtual ~ServerNode();

  bool getVersion(std::string *buffer, Error *error) const;

  bool start(Error *error);
  bool stop(Error *error);

  bool getRequestAddress(std::string *address, Error *error) const;
  bool getRequestPort(int *port, Error *error) const;
  
protected:

  void setRequestAddress(const std::string &host) {
    this->serverAddress = host;
  }
  
  void setRequestPort(int port) {
    this->serverPort = port;
  }
  
  bool isRpcRequest(uHTTP::HTTPRequest *httpReq);
  HttpStatusCode httpRpcRequestReceived(uHTTP::HTTPRequest *httpReq);

private:
  
  HttpStatusCode postRpcErrorResponse(uHTTP::HTTPRequest *httpReq, int rpcErrorCode);
  HttpStatusCode postRpcRequest(uHTTP::HTTPRequest *httpReq, Message *nodeReq);
  
  int serverPort;
  std::string serverAddress;
};

}

#endif
