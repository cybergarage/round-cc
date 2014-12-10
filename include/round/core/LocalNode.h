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
  void post(const NodeResponse *nodeRes, uHTTP::HTTPRequest *httpReq);
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
  
  bool isSystemMethod(const std::string &method);
  bool execSystemMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool getNodeInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool getClusterInfo(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool getClusterList(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

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

class SystemMethodRequest {
 public:
  static const std::string PREFIX;
  
  static const std::string SET_METHOD;
  static const std::string GET_NODE_INFO;
  static const std::string GET_CLUSTER_INFO;
  static const std::string GET_CLUSTER_LIST;
  
  static const std::string LANGUAGE;
  static const std::string NAME;
  static const std::string CODE;
  
 public:
  SystemMethodRequest(NodeRequest *ndoeReq);
    
 private:
  NodeRequest *nodeReq;
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
  SystemMethodResponse(NodeResponse *ndoeRes);
  
private:
  NodeResponse *nodeRes;
};
  
}

#endif
