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

#include <round/Const.h>
#include <round/core/Method.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>
#include <round/core/Registry.h>

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

class SystemMethodResponse {
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

// remove_method

class remove_method : public system_method {
public:
  static const std::string NAME;
  static const std::string METHOD_NAME;
public:
  remove_method();
  ~remove_method();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
// post_job
  
class post_job : public system_method {
public:
  static const std::string NAME;
  static const std::string JOB_LANGUAGE;
  static const std::string JOB_CODE;
  static const std::string JOB_ENCODE;
  static const std::string JOB_ENCODE_BASE64;
public:
  post_job();
  ~post_job();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

// set_route
  
class set_route : public system_method {
public:
  static const std::string NAME;
  static const std::string ROUTE_NAME;
  static const std::string ROUTE_SRC;
  static const std::string ROUTE_DEST;
  static const std::string ROUTE_TYPE;
  static const std::string ROUTE_PIPE;
  static const std::string ROUTE_EVENT;
  static const std::string ROUTE_COND;
public:
    set_route();
    ~set_route();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

// remove_route

class remove_route : public system_method {
public:
  static const std::string NAME;
  static const std::string ROUTE_NAME;
  static const std::string ROUTE_SRC;
  static const std::string ROUTE_DEST;
public:
  remove_route();
  ~remove_route();
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

// remove_timer

class remove_timer : public system_method {
public:
  static const std::string NAME;
public:
  remove_timer();
  ~remove_timer();
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

// remove_alias

class remove_alias : public system_method {
public:
  static const std::string NAME;
public:
  remove_alias();
  ~remove_alias();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
// get_node_state

class get_node_state : public system_method {
public:
  static const std::string NAME;
public:
  get_node_state();
  ~get_node_state();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemNodeInfoDict {
public:
  static const std::string NAME;
  static const std::string ADDR;
  static const std::string PORT;
  static const std::string HASH;
  static const std::string VER;
  static const std::string CLUSTER;
  static const std::string STATE;
  
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
  
  bool setAddress(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(ADDR, value) : false;
  }
  
  bool getAddress(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(ADDR, value) : false;
  }
  
  bool setPort(int value) {
    return (this->jsonDict) ? this->jsonDict->set(PORT, value) : false;
  }
  
  bool getPort(int *value) const {
    return (this->jsonDict) ? this->jsonDict->get(PORT, value) : false;
  }
  
  bool setCluster(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(CLUSTER, value) : false;
  }
  
  bool getCluster(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(CLUSTER, value) : false;
  }
  
  bool setHash(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(HASH, value) : false;
  }
  
  bool getHash(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(HASH, value) : false;
  }
  
  bool setState(const std::string &value) {
    return (this->jsonDict) ? this->jsonDict->set(STATE, value) : false;
  }
  
  bool getState(std::string *value) const {
    return (this->jsonDict) ? this->jsonDict->get(STATE, value) : false;
  }
  
private:
  JSONDictionary *jsonDict;
};

class SystemGetNodeInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNodeInfoRequest() {
    setMethod(get_node_state::NAME);
  }
};

class SystemGetNodeInfoResponse : public SystemMethodResponse {
 public:
  SystemGetNodeInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setNode(Node *node) {
    return getNodeInfoDict()->setNode(node);
  }
  
  bool setAddress(const std::string &value) {
    return getNodeInfoDict()->setAddress(value);
  }
  
  bool getAddress(std::string *value) const {
    return getNodeInfoDict()->getAddress(value);
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

// get_node_config
  
class get_node_config : public system_method {
public:
  static const std::string NAME;
public:
  get_node_config();
  ~get_node_config();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
// get_cluster_state

class get_cluster_state : public system_method {
public:
  static const std::string NAME;
public:
  get_cluster_state();
  ~get_cluster_state();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemClusterInfoDict {
public:
  static const std::string NAME;
  static const std::string NODES;
  static const std::string CLUSTER;
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
    setMethod(get_cluster_state::NAME);
  }
};
  
class SystemGetClusterInfoResponse : public SystemMethodResponse {
  static const std::string NODES;
  static const std::string CLUSTER;
 public:
  SystemGetClusterInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setCluster(LocalNode *node);
  bool getCluster(Cluster *cluster);
  
  JSONDictionary *getResultClusterDict();
  JSONArray *getResultClusterNodeArray();
};

class SystemGetNetworkInfoResponse : public SystemMethodResponse {
  static const std::string CLUSTERS;
 public:
  SystemGetNetworkInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }
    
  bool setClusters(LocalNode *node);
  bool getClusters(ClusterList *clusterList);
    
  JSONArray *getResultClusterArray();
};

// get_network_state

class get_network_state : public system_method {
public:
  static const std::string NAME;
public:
  get_network_state();
  ~get_network_state();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemGetNetworkInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNetworkInfoRequest() {
    setMethod(get_network_state::NAME);
  }
};
  
// set_registry

class set_registry : public system_method {
 public:
  static const std::string NAME;
 public:
  set_registry();
  ~set_registry();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemSetRegistryRequest : public SystemMethodRequest {
 public:
  SystemSetRegistryRequest() {
    setMethod(set_registry::NAME);
  }
  
  void setRegistry(const Registry reg);
};

// get_registry

class get_registry : public system_method {
public:
  static const std::string NAME;
public:
  get_registry();
  ~get_registry();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};

class SystemGetRegistryRequest : public SystemMethodRequest {
public:
  SystemGetRegistryRequest() {
    setMethod(get_registry::NAME);
  }

  void setKey(const std::string &value);
};

class SystemGetRegistryResponse : public SystemMethodResponse {
  public:
    SystemGetRegistryResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
    }
  
    bool setRegistry(const Registry reg);
    bool getRegistry(Registry *reg);
};

// remove_registry

class remove_registry : public system_method {
public:
  static const std::string NAME;
public:
  remove_registry();
  ~remove_registry();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
class SystemRemoveRegistryRequest : public SystemMethodRequest {
public:
  SystemRemoveRegistryRequest() {
    setMethod(remove_registry::NAME);
  }
  
  void setKey(const std::string &value);
};

// exec
  
class execp : public system_method {
public:
  static const std::string NAME;
  static const std::string CMD;
  static const std::string ARGS;
public:
  execp();
  ~execp();
  bool exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const;
};
  
}

#endif
