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
#include <round/common/Config.h>
#include <round/core/Node.h>
#include <round/core/NodeGraph.h>
#include <round/core/NodeFinder.h>
#include <round/core/Script.h>
#include <round/core/Method.h>
#include <round/core/Route.h>
#include <round/core/Registry.h>

namespace Round {

class LocalNode;

class LocalWorkder : public Thread<LocalNode> {
 public:
  LocalWorkder();
  ~LocalWorkder();

  void run();
  
 private:
  void post(uHTTP::HTTPRequest *httpReq, const NodeResponse *nodeRes);
  void post(uHTTP::HTTPRequest *httpReq, const NodeBatchResponse *nodeBatchRes);
};

class LocalScriptManager : public ScriptManager {
 public:
  static const std::string SYSTEM_ECHO_METHOD_CODE;
  static const std::string SYSTEM_ECHO_METHOD_LANGUAGE;
  
 public:
  LocalScriptManager();
  ~LocalScriptManager();
  
 private:
  void init();
};

class LocalStaticMethodManager : public MethodManager {
public:
  LocalStaticMethodManager();
  ~LocalStaticMethodManager();
    
private:
  void init();
};
  
class LocalNativeMethodManager : public MethodManager {
  public:
    LocalNativeMethodManager();
    ~LocalNativeMethodManager();
    
  private:
    void init();
};

class LocalRegistry : public RegistryManager {
    
public:
    
  LocalRegistry();
  ~LocalRegistry();

  void setNode(LocalNode *node);

  bool set(const Registry reg);
  bool set(const std::string &key, const std::string &value);

private:
  
  LocalNode *node;
};

class LocalRouteManager: public RouteManager {
    
public:
    
  LocalRouteManager();
  ~LocalRouteManager();

private:
  void init();
};
  
class LocalConfig : public Config {
 public:
  
  static const std::string BIND_ADDR;
  static const std::string BIND_PORT;
  static const std::string CLUSTER;
  static const std::string LOG_FILE;
  static const std::string METHODS;

  static const std::string DEFALUT_CLUSTER;
  static const std::string AUTO;
  static int BIND_PORT_RANGE_MIN;
  static int BIND_PORT_RANGE_MAX;
  
 public:
  LocalConfig();
  ~LocalConfig();

  bool isValid(Error *error);

 public:
  
  bool getBindAddress(std::string *value, Error *error) const;
  bool getBindPort(int *value, Error *error) const;
  bool getCluster(std::string *value, Error *error) const;
  bool getLogFilename(std::string *value, Error *error) const;

  bool setBindAddress(const std::string &value, Error *error);
  bool setBindPort(int value, Error *error);
  bool setCluster(const std::string &value, Error *error);
  bool setLogFilename(const std::string &value, Error *error);  
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
  bool setScript(const std::string &method, const std::string &lang, const std::string &script, int encodeType, Error *error);
  bool removeScript(const std::string &method, Error *error);
  
  bool execJob(const std::string &lang, const std::string &script, int encodeType, std::string *result, Error *error);
  
  bool setRegistry(const std::string &key, const std::string &value);
  bool getRegistry(const std::string &key, std::string *value) const;
  
  bool setRegistry(const Registry reg);
  bool getRegistry(const std::string &key, Registry *reg) const;
  bool removeRegistry(const std::string &key);

  bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool postMessage(const NodeBatchRequest *nodeReq, NodeBatchResponse *nodeRes, Error *error);
  
  bool loadConfigFromString(const std::string &string, Error *error);
  bool loadConfigFromFile(const std::string &filename, Error *error);
  bool isConfigValid(Error *error);
  bool getConfig(JSONDictionary *jsonDict, Error *error);
  
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

  bool pushMessage(const Message *nodeReq);
  bool waitMessage(const Message **nodeReq);
  bool execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool execMessage(const NodeBatchRequest *nodeReq, NodeBatchResponse *nodeRes, Error *error);

  bool setRoute(Route *route);
  bool removeSameRoute(const Route *route);
  bool removeRouteByName(const std::string &name);
  
  virtual bool start(Error *error);
  virtual bool stop(Error *error);
  
  bool restart(Error *error);
  
  LocalConfig *getConfig() {
    return &this->nodeConfig;
  }

  bool setBindAddress(const std::string &value, Error *error) {
    return this->nodeConfig.setBindAddress(value, error);
  }
  
  bool setBindPort(int value, Error *error) {
    return this->nodeConfig.setBindPort(value, error);
  }
  
  bool setCluster(const std::string &value, Error *error) {
    return this->nodeConfig.setCluster(value, error);
  }
  
  NodeGraph *getNodeGraph() {
    return &this->nodeGraph;
  }
  
  bool isCloneable() const {
    return false;
  }

  bool getQuorumNodes(NodeList *nodes, size_t quorum);
  bool getAllOtherNodes(NodeList *nodes);

  bool isStaticMethod(const std::string &method);

  NodeStatus::State getState() const {
    return this->nodeStatus.getState();
  }
  
  const char *getStateString() const {
    return this->nodeStatus.getStateString();
  }
  
protected:

  void setState(NodeStatus::State value) {
    this->nodeStatus.setState(value);
  }

private:

  void init();

  bool execMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  bool setError(int rpcErrorCode, Error *err);
  
  bool execStaticMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool isDynamicMethod(const std::string &method);
  bool execDynamicMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool isNativeMethod(const std::string &method);
  bool execNativeMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

  bool hasRounte(const std::string &name);
  bool execRoute(const std::string &name, const NodeResponse *prevNodeRes, NodeResponse *nodeRes, Error *error);
  
private:

  NodeGraph               nodeGraph;
  NodeStatus              nodeStatus;
  
  NodeMessageManager        nodeMsgMgr;
  
  LocalConfig               nodeConfig;
  LocalWorkder              nodeWorker;
  LocalScriptManager        scriptMgr;
  LocalStaticMethodManager  staticMethodMgr;
  LocalNativeMethodManager  sysMethodMgr;
  LocalRegistry             nodeReg;
  LocalRouteManager         routeMgr;
};

}

#endif
