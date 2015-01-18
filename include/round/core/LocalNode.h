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
#include <round/core/NodeConfig.h>
#include <round/core/Script.h>
#include <round/core/Method.h>

namespace Round {

class LocalNode;

class LocalWorkder : public Thread<LocalNode> {
 public:
  LocalWorkder();
  ~LocalWorkder();

  void run();
  
 private:
  void post(uHTTP::HTTPRequest *httpReq, const NodeResponse *nodeRes);
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

class LocalMemory : public std::map<std::string, std::string> {
    
public:
    
  LocalMemory();
  ~LocalMemory();
  
  bool setKey(const std::string &key, const std::string &value);
  bool getKey(const std::string &key, std::string *value) const;
};

class LocalConfig : public NodeConfig {
 public:
  static const std::string DEFAULT_FILENAME;
  static const std::string AUTO;
  static const int DEFAULT_HTTPD_PORT;

  enum Sections {
    General = 0,
    Httpd,
    Log,
    SectionCount,
  };

  enum GeneralSectionKeys {
    Cluster = 0,
    DatabaseDir,
    GeneralKeyCount,
  };

  enum HttpdSectionKeys {
    HttpdBindAddress = 0,
    HttpdBindPort,
    HttpdKeyCount,
  };

  enum LogSectionKeys {
    LogFile = 0,
    ErrorLogFile,
    LogLevel,
    LogKeyCount,
  };

 public:
  LocalConfig();
  ~LocalConfig();

  bool isValid(Error *error);

  size_t getSectionCount() const;
  size_t getSectionKeyCount(size_t section) const;
  
  const char *getSectionKeyString(size_t section, size_t n) const;
  const char *getSectionString(size_t n) const;

 public:
  bool getHttpdBindAddress(std::string *value, Error *error) const;
  bool getHttpdBindPort(int *value, Error *error) const;

  bool getCluster(std::string *value, Error *error) const {
    return getValue(General, Cluster, value, error);
  }
  
  bool getDatabaseDirectory(std::string *value, Error *error) const {
    return getValue(General, DatabaseDir, value, error);
  }

  bool getLogFilename(std::string *value, Error *error) const {
    return getValue(Log, LogFile, value, error);
  }

  bool getErrorLogFilename(std::string *value, Error *error) const {
    return getValue(Log, ErrorLogFile, value, error);
  }

  bool setHttpdBindAddress(const std::string &value) {
    return setValue(Httpd, HttpdBindAddress, value);
  }
  
  bool setHttpdBindPort(int port) {
    return setValue(Httpd, HttpdBindPort, port);
  }
  
  bool setCluster(const std::string &value) {
    return setValue(General, Cluster, value);
  }
  
  bool setDatabaseDirectory(const std::string &value) {
    return setValue(General, DatabaseDir, value);
  }

  bool setLogFilename(const std::string &value) {
    return setValue(Log, LogFile, value);
  }
  
  bool setErrorLogFilename(const std::string &value) {
    return setValue(Log, ErrorLogFile, value);
  }
  
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
  
  LocalConfig *getNodeConfig() {
    return &this->nodeConfig;
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
  
  bool execStaticMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool isDynamicMethod(const std::string &method);
  bool execDynamicMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);
  
  bool isNativeMethod(const std::string &method);
  bool execNativeMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error);

private:

  NodeGraph               nodeGraph;
  NodeStatus              nodeStatus;
  
  NodeMessageManager        nodeMsgMgr;
  
  LocalConfig               nodeConfig;
  LocalWorkder              nodeWorker;
  LocalScriptManager        scriptMgr;
  LocalStaticMethodManager  staticMethodMgr;
  LocalNativeMethodManager  sysMethodMgr;
  LocalMemory               memory;
};

}

#endif
