/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
#include <round/core/Method.h>

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
  static const std::string SYSTEM_ECHO_METHOD_CODE;
  static const std::string SYSTEM_ECHO_METHOD_LANGUAGE;
  
 public:
  LocalNodeScriptManager();
  ~LocalNodeScriptManager();

 private:
  void init();
};

class LocalNodeStaticMethodManager : public MethodManager {
  public:
    LocalNodeStaticMethodManager();
    ~LocalNodeStaticMethodManager();
    
  private:
    void init();
};

class LocalMemory : public std::map<std::string, std::string> {
    
public:
    
  LocalMemory();
  ~LocalMemory();
  
  bool setKey(const std::string &key, const std::string &value);
  bool getKey(const std::string &key, std::string *value) const;
};
  
/**
 * LocalNode is a real implementation of Node class.
 */
class LocalNode : public Node, public NodeFinderObserver {
 public:
  
 public:
  LocalNode();
  virtual ~LocalNode();

  bool getClusterName(std::string *name, Error *error);
  
  bool addMethod(Method *method);
  
  bool setKey(const std::string &key, const std::string &value);
  bool getKey(const std::string &key, std::string *value) const;
  
  bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool loadConfigFromString(const std::string &string, Error *error);
  bool loadConfigFromFile(const std::string &filename, Error *error);
  bool isConfigValid(Error *error);
  
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

  bool pushMessage(const Message *nodeReq);
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

public:
  
  bool getQuorumNodes(NodeList *nodes, size_t quorum);
  bool getAllOtherNodes(NodeList *nodes);

protected:

  void setState(NodeStatus::State value) {
    this->nodeStatus.setState(value);
  }

  NodeStatus::State getState() {
    return this->nodeStatus.getState();
  }

private:

  void init();

  bool execMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool setError(int rpcErrorCode, Error *err);
  
  bool is_set_method(const std::string &method);
  bool _set_method(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool hasDynamicMethod(const std::string &method);
  bool execDynamicMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool hasNativeMethod(const std::string &method);
  bool execNativeMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

private:

  NodeGraph               nodeGraph;
  NodeStatus              nodeStatus;
  
  NodeMessageManager            nodeMsgMgr;
  
  LocalNodeConfig               nodeConfig;
  LocalNodeWorkder              nodeWorker;
  LocalNodeScriptManager        scriptMgr;
  LocalNodeStaticMethodManager  sysMethodMgr;
  LocalMemory                   memory;
};

}

#endif
