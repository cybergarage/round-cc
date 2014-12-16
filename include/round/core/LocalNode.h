/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_LOCALNODE_H_
#define _ROUNDCC_LOCALNODE_H_

#include <round/common/Thread.h>
#include <round/core/Node.h>
#include <round/core/NodeGraph.h>
#include <round/core/NodeFinder.h>
#include <round/core/LocalNodeConfig.h>
#include <round/core/Script.h>

namespace Round {

class LocalNode;

class LocalNodeWorkder : public Thread<LocalNode> {
 public:
  LocalNodeWorkder();
  ~LocalNodeWorkder();

  void run();
  
 private:
  void post(uHTTP::HTTPRequest *httpReq, const NodeResponse *nodeRes);
};

class LocalNodeScriptManager : public ScriptManager {
 public:
  LocalNodeScriptManager();
  ~LocalNodeScriptManager();

 private:
  void init();
};

/**
 * LocalNode is a real implementation of Node class.
 */
class LocalNode : public Node, public NodeFinderObserver {
 public:
  
 public:
  LocalNode();
  virtual ~LocalNode();

  bool getClusterName(std::string *name, Error *error) const;
  bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool loadConfigFromString(const std::string &string, Error *error);
  bool loadConfigFromFile(const std::string &filename, Error *error);
  bool isConfigValid(Error *error);
  
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

  bool pushMessage(const NodeRequest *nodeReq);
  bool waitMessage(const NodeRequest **nodeReq);
  bool execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  virtual bool start(Error *error);
  virtual bool stop(Error *error);
  bool restart(Error *error);
  
  LocalNodeConfig *getNodeConfig() {
    return &this->nodeConfig;
  }

  NodeGraph *getNodeGraph() {
    return &this->nodeGraph;
  }
  
  bool isCloneable() const {
    return false;
  }
  
 protected:

  void setState(NodeStatus::State value) {
    this->nodeStatus.setState(value);
  }

  NodeStatus::State getState() {
    return this->nodeStatus.getState();
  }

private:

  void init();

  bool isSetMethod(const std::string &method);
  bool setMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool hasUserMethod(const std::string &method);
  
  bool setError(int rpcErrorCode, Error *err);

  bool isSystemMethod(const std::string &method);
  bool execSystemMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool getNodeInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool getClusterInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool getNetworkInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

private:

  LocalNodeConfig         nodeConfig;
  NodeGraph               nodeGraph;
  NodeStatus              nodeStatus;
  
  NodeMessageManager      nodeMsgMgr;
  LocalNodeWorkder        nodeWorker;
  LocalNodeScriptManager  scriptMgr;
};


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
    static const std::string VERSION;
    static const std::string CLUSTER;
    static const std::string CLUSTERS;
    
public:
    SystemMethodResponse(NodeResponse *nodeRes);
    
 protected:
    NodeResponse *nodeRes;
};
  
class SystemGetNodeInfoResponse : public SystemMethodResponse {
 public:
  SystemGetNodeInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setIp(const std::string &value) {
    return nodeRes->set(IP, value);
  }
  
  bool getIp(std::string *value) const {
    return nodeRes->get(IP, value);
  }

  bool setPort(int value) {
    return nodeRes->set(IP, value);
  }
  
  bool getPort(int *value) const {
    return nodeRes->get(IP, value);
  }
  
  bool setCluster(const std::string &value) {
    return nodeRes->set(CLUSTER, value);
  }
  
  bool getCluster(std::string *value) const {
    return nodeRes->get(CLUSTER, value);
  }

  bool setHash(const std::string &value) {
    return nodeRes->set(HASH, value);
  }
  
  bool getHash(std::string *value) const {
    return nodeRes->get(HASH, value);
  }
};


}

#endif
