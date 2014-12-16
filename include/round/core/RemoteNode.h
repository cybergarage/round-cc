/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
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
  
  RemoteNode(const Node *node);
  RemoteNode(const std::string &address, int port);
  virtual ~RemoteNode();

 public:
  
  bool getRequestPort(int *port, Error *error) const;
  bool getRequestAddress(std::string *address, Error *error) const;
  bool getClusterName(std::string *name, Error *error);

  bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

  bool isCloneable() const {
    return true;
  }
  
  Node *clone() const;
  
private:

  std::string requestAddress;
  int requestPort;

};

}

#endif
