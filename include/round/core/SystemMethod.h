/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SYSTEMMETHOD_H_
#define _ROUNDCC_SYSTEMMETHOD_H_

#include <round/core/Node.h>
#include <round/core/NodeMessage.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>

namespace Round {

/**
 * SystemMethodResponse uses to create a response message for system methods.
 */

class SystemMethodRequest : public NodeRequest {
 public:
  static const std::string PREFIX;
  
  static const std::string SET_METHOD;
  static const std::string GET_NODE_INFO;
  static const std::string GET_CLUSTER_INFO;
  static const std::string GET_NETWORK_INFO;
  
  static const std::string LANGUAGE;
  static const std::string NAME;
  static const std::string CODE;
  
 public:
  SystemMethodRequest();

 private:
};

class SystemGetNodeInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNodeInfoRequest() {
    setMethod(GET_NODE_INFO);
  }
};

class SystemGetClusterInfoRequest : public SystemMethodRequest {
 public:
  SystemGetClusterInfoRequest() {
      setMethod(GET_CLUSTER_INFO);
  }
};

class SystemGetNetworkInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNetworkInfoRequest() {
    setMethod(GET_NETWORK_INFO);
  }
};
  
/**
 * SystemMethodResponse uses to create a response message for system methods.
 */

class SystemMethodResponse {
  public:
    static const std::string NAME;
    static const std::string IP;
    static const std::string PORT;
    static const std::string HASH;
    static const std::string VER;
    static const std::string CLUSTER;
    static const std::string NODES;
    static const std::string CLUSTERS;
    
public:
    SystemMethodResponse(NodeResponse *nodeRes);
    
 protected:
    NodeResponse *nodeRes;
};

class SystemNodeInfoDict {
public:
  SystemNodeInfoDict() {
    setJSONDictionary(NULL);
  }
  
  SystemNodeInfoDict(JSONDictionary *jsonDict) {
    setJSONDictionary(jsonDict);
  }

  void setJSONDictionary(JSONDictionary *jsonDict) {
    this->jsonDict = jsonDict;
  }
  
  bool setNode(Node *node);
  bool getNode(RemoteNode *node);
  
  bool setIp(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(SystemMethodResponse::IP, value) : false;
  }
  
  bool getIp(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(SystemMethodResponse::IP, value) : false;
  }
  
  bool setPort(int value) {
    return (this->jsonDict) ? this->jsonDict->set(SystemMethodResponse::PORT, value) : false;
  }
  
  bool getPort(int *value) const {
    return (this->jsonDict) ? this->jsonDict->get(SystemMethodResponse::PORT, value) : false;
  }
  
  bool setCluster(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(SystemMethodResponse::CLUSTER, value) : false;
  }
  
  bool getCluster(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(SystemMethodResponse::CLUSTER, value) : false;
  }
  
  bool setHash(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(SystemMethodResponse::HASH, value) : false;
  }
  
  bool getHash(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(SystemMethodResponse::HASH, value) : false;
  }
  
private:
  JSONDictionary *jsonDict;
};

class SystemClusterInfoDict {
 public:
  SystemClusterInfoDict() {
    setJSONDictionary(NULL);
  }
    
  SystemClusterInfoDict(JSONDictionary *jsonDict) {
    setJSONDictionary(jsonDict);
  }
    
  void setJSONDictionary(JSONDictionary *jsonDict) {
    this->jsonDict = jsonDict;
  }
    
  JSONArray *getNodeArray();
  
  bool setCluster(LocalNode *node);
  bool getCluster(Cluster *cluster);
  
  private:
    JSONDictionary *jsonDict;
};
  
class SystemGetNodeInfoResponse : public SystemMethodResponse {
 public:
  SystemGetNodeInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setNode(Node *node) {
    return getNodeInfoDict()->setNode(node);
  }
  
  bool setIp(const std::string &value) {
    return getNodeInfoDict()->setIp(value);
  }
  
  bool getIp(std::string *value) const {
    return getNodeInfoDict()->getIp(value);
  }
  
  bool setPort(int value) {
    return getNodeInfoDict()->setPort(value);
  }
  
  bool getPort(int *value) const {
    return getNodeInfoDict()->getPort(value);
  }
  
  bool setCluster(const std::string &value) {
    return getNodeInfoDict()->setCluster(value);
  }
  
  bool getCluster(std::string *value) const {
    return getNodeInfoDict()->getCluster(value);
  }
  
  bool setHash(const std::string &value) {
    return getNodeInfoDict()->setHash(value);
  }
  
  bool getHash(std::string *value) const {
    return getNodeInfoDict()->getHash(value);
  }

private:
  
  SystemNodeInfoDict *getNodeInfoDict() const {
    this->nodeInfoDict.setJSONDictionary(nodeRes->getResultDict());
    return &this->nodeInfoDict;
  }
  
  mutable SystemNodeInfoDict nodeInfoDict;
};

class SystemGetClusterInfoResponse : public SystemMethodResponse {
 public:
  SystemGetClusterInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setCluster(LocalNode *node);
  bool getCluster(Cluster *cluster);
  
  JSONDictionary *getResultClusterDict();
  JSONArray *getResultClusterNodeArray();
};

class SystemGetNetworkInfoResponse : public SystemMethodResponse {
 public:
  SystemGetNetworkInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }
    
  bool setClusters(LocalNode *node);
  bool getClusters(ClusterList *clusterList);
    
  JSONArray *getResultClusterArray();
};
  
}

#endif
