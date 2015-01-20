/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_REMOTENODE_H_
#define _ROUNDCC_REMOTENODE_H_

#include <round/core/Node.h>

#include <uhttp/http/HTTPStatus.h>

namespace Round {
  
class RemoteNode : public Node {
 public:
  
  RemoteNode();
  RemoteNode(Node *node);
  RemoteNode(const std::string &address, int port);
  virtual ~RemoteNode();

 public: 
  
  bool getRequestAddress(std::string *address, Error *error) const;
  bool getRequestPort(int *port, Error *error) const;
  bool getClusterName(std::string *name, Error *error);
  
  bool setRequestAddress(const std::string &address);
  bool setRequestPort(int port);
  bool setClusterName(const std::string &name);
  
  bool hasClusterName() {
    return (0 < this->clusterName.length()) ? true : false;
  }

  bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool getMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error, bool jsonRpcEncodeEnable);
  bool postRPC(const std::string &s , Error *error);

  bool isCloneable() const {
    return true;
  }
  
  Node *clone();
  
private:

  bool setUpdatedNodeStatusParameters(const NodeRequest *nodeReq);
  bool postMessage(uHTTP::HTTPRequest *httpReq, NodeResponse *nodeRes, Error *error);

private:

  std::string requestAddress;
  int requestPort;
  std::string clusterName;

};

}

#endif
