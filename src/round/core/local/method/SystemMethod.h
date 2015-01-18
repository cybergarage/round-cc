/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SYSTEMMETHOD_H_
#define _ROUNDCC_SYSTEMMETHOD_H_

#include <round/core/Method.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>

namespace Round {

class system_method : public Method {
public:
  static const std::string ECHO;  
public:
  system_method(const std::string &name);
  ~system_method();
  
  bool exec(const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
  virtual bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const = 0;
};

class SystemMethodRequest : public NodeRequest {
 public:
  SystemMethodRequest();
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

// _echo
  
class SystemEchoRequest : public SystemMethodRequest {
 public:
  SystemEchoRequest() {
    setMethod(system_method::ECHO);
  }
};

// set_method
  
class set_method : public system_method {
 public:
  static const std::string NAME;
  static const std::string METHOD_LANGUAGE;
  static const std::string METHOD_NAME;
  static const std::string METHOD_CODE;
  static const std::string METHOD_ENCODE;
  static const std::string METHOD_ENCODE_BASE64;
 public:
  set_method();
  ~set_method();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

// set_route
  
class set_route : public system_method {
  public:
    static const std::string NAME;
  public:
    set_route();
    ~set_route();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

// set_timer
  
class set_timer : public system_method {
public:
  static const std::string NAME;
public:
  set_timer();
  ~set_timer();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

// set_alias
  
class set_alias : public system_method {
 public:
  static const std::string NAME;
 public:
  set_alias();
  ~set_alias();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
// get_node_info

class get_node_info : public system_method {
public:
  static const std::string NAME;
public:
  get_node_info();
  ~get_node_info();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
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

class SystemGetNodeInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNodeInfoRequest() {
    setMethod(get_node_info::NAME);
  }
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

// get_cluster_info

class get_cluster_info : public system_method {
public:
  static const std::string NAME;
public:
  get_cluster_info();
  ~get_cluster_info();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
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
  
class SystemGetClusterInfoRequest : public SystemMethodRequest {
public:
  SystemGetClusterInfoRequest() {
    setMethod(get_cluster_info::NAME);
  }
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

// get_network_info

class get_network_info : public system_method {
public:
  static const std::string NAME;
public:
  get_network_info();
  ~get_network_info();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemGetNetworkInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNetworkInfoRequest() {
    setMethod(get_network_info::NAME);
  }
};
  
// set_key

class set_key : public system_method {
 public:
  static const std::string NAME;
  static const std::string KEY;
  static const std::string VALUE;
 public:
  set_key();
  ~set_key();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemSetKeyRequest : public SystemMethodRequest {
 public:
  SystemSetKeyRequest() {
    setMethod(set_key::NAME);
  }
  
  void setKey(const std::string &value) {
    set(set_key::KEY, value);
  }

  void setValue(const std::string &value) {
    set(set_key::VALUE, value);
  }
};

// get_key

class get_key : public system_method {
public:
  static const std::string NAME;
  static const std::string KEY;
public:
  get_key();
  ~get_key();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemGetKeyRequest : public SystemMethodRequest {
public:
  SystemGetKeyRequest() {
    setMethod(get_key::NAME);
  }

  void setKey(const std::string &value) {
    set(get_key::KEY, value);
  }
};
  
}

#endif
