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

#include <uhttp/http/HTTPStatus.h>

#include <round/core/Node.h>
#include <round/core/JSONRequest.h>
#include <round/core/JSONResponse.h>

namespace Round {
  
class RemoteNode : public Node {
 public:
  
  RemoteNode(const Node *node);
  RemoteNode(const std::string &address, int port);
  virtual ~RemoteNode();

 public:
  
  int getRequestPort() const {
    return this->requestPort;
  }

  const char *getRequestAddress() const {
    return this->requestAddress.c_str();
  }

  bool getCluster(Cluster *cluster, Error *error) const;
  bool getName(std::string *buffer, Error *error) const;
  bool getVersion(std::string *buffer, Error *error) const;
  bool getStatus(NodeStatus *status, Error *error) const;

  bool getTabletSpaces(TabletSpaceList *tabletSpaceList, Error *error);

  bool getNodeGraph(NodeGraph *nodeGraph, Error *error);

  bool postMessage(const Message *msg);

  bool isCloneable() const {
    return true;
  }
  
  Node *clone() const;
  
private:

  void setJSONResponseError(Error *error) const;
  int postJSONRequest(const std::string &method, const std::string &uri, const JSONObject *jsonContent, JSONObject **jsonResponse, Error *error) const;

private:

  std::string requestAddress;
  int requestPort;

};

}

#endif
