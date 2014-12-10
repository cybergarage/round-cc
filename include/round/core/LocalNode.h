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

class LocalNode : public Node, public NodeFinderObserver {
 public:
  
  static const std::string SYSTEM_STATIC_METHOD_SET_METHOD;
  static const std::string SYSTEM_STATIC_METHOD_SET_METHOD_LANGUAGE;
  static const std::string SYSTEM_STATIC_METHOD_SET_METHOD_NAME;
  static const std::string SYSTEM_STATIC_METHOD_SET_METHOD_CODE;
  
  static const std::string SYSTEM_DYNAMIC_METHOD_GET_NODE_INFO;
  static const std::string SYSTEM_DYNAMIC_METHOD_GET_CLUSTER_INFO;
  static const std::string SYSTEM_DYNAMIC_METHOD_GET_CLUSTER_LIST;
  
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
  
  bool isSetMethod(const std::string &method);
  bool setMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool isSystemMethod(const std::string &method);
  bool execSystemMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
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

private:

  LocalNodeConfig         nodeConfig;
  NodeGraph               nodeGraph;
  NodeStatus              nodeStatus;
  
  NodeMessageManager      nodeMsgMgr;
  LocalNodeWorkder        nodeWorker;
  LocalNodeScriptManager  scriptMgr;
};

}

#endif
