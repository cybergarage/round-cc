/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <round/Round.h>
#include <round/core/LocalNode.h>
#include <round/core/RemoteNode.h>
#include <round/core/local/method/SystemMethod.h>

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::LocalNode::LocalNode() {
  init();
}

Round::LocalNode::~LocalNode() {
}

void Round::LocalNode::init() {
  this->nodeReg.setNode(this);
  this->scriptMgr.setNode(this);
  setState(NodeStatus::STOP);
}

////////////////////////////////////////////////
// Config
////////////////////////////////////////////////

bool Round::LocalNode::loadConfigFromString(const std::string &string, Error *error) {
  if (this->nodeConfig.loadFromString(string, error) == false)
    return false;
  return true;
}

bool Round::LocalNode::loadConfigFromFile(const std::string &filename, Error *error) {
  if (this->nodeConfig.loadFromFile(filename, error) == false)
    return false;
  return true;
}

bool Round::LocalNode::isConfigValid(Error *error) {
  return this->nodeConfig.isValid(error);
}

bool Round::LocalNode::getClusterName(std::string *name, Error *error) {
  return this->nodeConfig.getCluster(name, error);
}

bool Round::LocalNode::getConfig(JSONDictionary *jsonDict, Error *error) {
  std::string value;
  int ivalue;

  // bind_addr
  if (this->nodeConfig.getBindAddress(&value, error)) {
    jsonDict->set(LocalConfig::BIND_ADDR, value);
 }
 
  // bind_port
  if (this->nodeConfig.getBindPort(&ivalue, error)) {
    jsonDict->set(LocalConfig::BIND_PORT, ivalue);
  }
  
  // cluster
  if (getClusterName(&value, error)) {
    jsonDict->set(LocalConfig::CLUSTER, value);
  }
  
  // log_file
  if (this->nodeConfig.getLogFilename(&value, error)) {
    jsonDict->set(LocalConfig::LOG_FILE, value);
  }
  
  // methods
  JSONArray *methods = new JSONArray();
  if (methods) {
    if (this->scriptMgr.toJSONArray(methods, error)) {
      jsonDict->set(LocalConfig::METHODS, methods);
    }
    else {
      delete methods;
    }
  }

  return true;
}

////////////////////////////////////////////////
// Thread
////////////////////////////////////////////////

bool Round::LocalNode::start(Error *error) {
  stop(error);
  
  bool areAllOperationSucess = true;
  
  setState(NodeStatus::ACTIVATING);

  nodeWorker.setObject(this);
  if (nodeWorker.start()) {
    if (!this->nodeGraph.addNode(this)) {
      areAllOperationSucess = false;
    }
  }
  else {
    areAllOperationSucess = false;
  }

  if (!this->triggerMgr.start()) {
    areAllOperationSucess = false;
  }
  
  if (!areAllOperationSucess) {
    stop(error);
    return false;
  }
  
  setState(NodeStatus::ACTIVE);
  
  return true;
}

bool Round::LocalNode::stop(Error *error) {
  bool areAllOperationSucess = true;
  
  if (!nodeWorker.stop()) {
    areAllOperationSucess = false;
    return false;
  }
  
  NodeGraph *nodeGraph = getNodeGraph();
  if (!nodeGraph->clear()) {
    areAllOperationSucess = false;
  }
  
  if (!this->triggerMgr.stop()) {
    areAllOperationSucess = false;
  }

  if (areAllOperationSucess == true) {
    setState(NodeStatus::STOP);
  }
  
  return areAllOperationSucess;
}

bool Round::LocalNode::restart(Error *error) {
  if (stop(error) == false)
    return false;
  return start(error);
}

////////////////////////////////////////////////
// Notification
////////////////////////////////////////////////

bool Round::LocalNode::nodeAdded(Round::Node *notifyNode)  {
  Error error;
  
  std::string notifyNodeCluster;
  if (!notifyNode->getClusterName(&notifyNodeCluster, &error))
    return false;
  
  std::string thisNodeCluster;
  if (!getClusterName(&thisNodeCluster, &error))
    return false;
  
  if (thisNodeCluster.compare(notifyNodeCluster) != 0)
    return false;
  
  if (this->nodeGraph.hasNode(notifyNode))
    return true;
  
  if (!this->nodeGraph.addNode(notifyNode))
    return true;
  
  if (equals(notifyNode))
    return true;
  
  return true;
}

bool Round::LocalNode::nodeRemoved(Round::Node *notifyNode)  {
  if (!this->nodeGraph.hasNode(notifyNode))
    return true;
  
  if (equals(notifyNode)) {
    this->nodeGraph.removeNode(notifyNode);
    return true;
  }
  
  ssize_t notifyNodeIndex = this->nodeGraph.getNodeIndex(notifyNode);
  if (notifyNodeIndex < 0)
    return false;
  
  Node *failedNode = this->nodeGraph.getNode(notifyNodeIndex);
  if (!failedNode)
    return false;
  
  return true;
}

////////////////////////////////////////////////
// Method
////////////////////////////////////////////////

bool Round::LocalNode::addMethod(Method *method) {
  return this->sysMethodMgr.addMethod(method);
}

bool Round::LocalNode::setScript(const std::string &method, const std::string &lang, const std::string &code, int encodeType, Error *error) {
  return this->scriptMgr.setScript(method, lang, code, encodeType, error);
}

bool Round::LocalNode::removeScript(const std::string &method, Error *error) {
  return this->scriptMgr.removeScript(method, error);
}

bool Round::LocalNode::execJob(const std::string &lang, const std::string &script, int encodeType, std::string *result, Error *error) {
  return this->scriptMgr.execScript(lang, script, encodeType, result, error);
}

////////////////////////////////////////////////
// Alias
////////////////////////////////////////////////

bool Round::LocalNode::setAlias(Alias *alias) {
  this->aliasMgr.lock();
  bool isSuccess = this->aliasMgr.setAlias(alias);
  this->aliasMgr.unlock();
  return isSuccess;
}

bool Round::LocalNode::removeAliasByName(const std::string &name) {
  this->aliasMgr.lock();
  bool isSuccess = this->aliasMgr.removeAliasByName(name);
  this->aliasMgr.unlock();
  return isSuccess;
}

////////////////////////////////////////////////
// Trigger
////////////////////////////////////////////////

bool Round::LocalNode::setTrigger(Trigger *trigger) {
  this->triggerMgr.lock();
  bool isSuccess = this->triggerMgr.setTrigger(trigger);
  this->triggerMgr.unlock();
  return isSuccess;
}

bool Round::LocalNode::removeTriggerByName(const std::string &name) {
  this->triggerMgr.lock();
  bool isSuccess = this->triggerMgr.removeTriggerByName(name);
  this->triggerMgr.unlock();
  return isSuccess;
}

bool Round::LocalNode::execTrigger(const std::string &name) {
  Error err;
  return execTrigger(name, &err);
}

////////////////////////////////////////////////
// Registry
////////////////////////////////////////////////

bool Round::LocalNode::setRegistry(const std::string &key, const std::string &value) {
  return this->nodeReg.set(key, value);
}

bool Round::LocalNode::getRegistry(const std::string &key, std::string *value) const {
  return this->nodeReg.get(key, value);
}

bool Round::LocalNode::setRegistry(const Registry reg) {
  return this->nodeReg.set(reg);
}

bool Round::LocalNode::getRegistry(const std::string &key, Registry *reg) const {
  return this->nodeReg.get(key, reg);
}

bool Round::LocalNode::removeRegistry(const std::string &key) {
  return this->nodeReg.remove(key);
}

////////////////////////////////////////////////
// Message
////////////////////////////////////////////////

bool Round::LocalNode::postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter
  (const_cast<NodeRequest *>(nodeReq))->setSourceNodeParameters(this);
  
  // Post RPC message
  return execMessage(nodeReq, nodeRes, error);
}

bool Round::LocalNode::postMessage(const NodeBatchRequest *nodeBatchReq, NodeBatchResponse *nodeBatchRes, Error *error) {
  return execMessage(nodeBatchReq, nodeBatchRes, error);
}

bool Round::LocalNode::pushMessage(const Message *nodeReq) {
  return this->nodeMsgMgr.pushMessage(nodeReq);
}

bool Round::LocalNode::waitMessage(const Message **nodeReq) {
  if (!this->nodeMsgMgr.waitMessage(nodeReq))
    return false;
  return true;
}

////////////////////////////////////////////////
// Route
////////////////////////////////////////////////

bool Round::LocalNode::setRoute(Route *route) {
  this->routeMgr.lock();
  
  bool isSuccess = this->routeMgr.setRoute(route);
  
  this->routeMgr.unlock();

  return isSuccess;
}

bool Round::LocalNode::removeSameRoute(const Route *route) {
  this->routeMgr.lock();
  
  bool isSuccess = this->routeMgr.removeSameRoute(route);
  
  this->routeMgr.unlock();
  
  return isSuccess;
}

bool Round::LocalNode::removeRouteByName(const std::string &name) {
  this->routeMgr.lock();
  
  bool isSuccess = this->routeMgr.removeRouteByName(name);
  
  this->routeMgr.unlock();
  
  return isSuccess;
}

////////////////////////////////////////////////
// get*Nodes
////////////////////////////////////////////////

bool Round::LocalNode::getQuorumNodes(NodeList *nodes, size_t quorum) {
  NodeGraph *nodeGraph = getNodeGraph();
  if (!nodeGraph)
    return false;
  
  for (size_t n=1; n<=quorum; n++) {
    Node *node = nodeGraph->getOffsetNode(this, n);
    if (!node)
      continue;
    if (node->equals(this))
      continue;
    RemoteNode *remoteNode = new RemoteNode(node);
    remoteNode->setWeakFlag(false);
    nodes->addNode(remoteNode);
  }
  
  return true;
}

bool Round::LocalNode::getAllOtherNodes(NodeList *nodes) {
  NodeGraph *nodeGraph = getNodeGraph();
  if (!nodeGraph)
    return false;
  
  nodeGraph->lock();
  
  for (NodeGraph::iterator nodeIt = nodeGraph->begin(); nodeIt != nodeGraph->end(); nodeIt++) {
    Node *node = dynamic_cast<Node *>(*nodeIt);
    if (!node)
      continue;
    if (node->equals(this))
      continue;
    RemoteNode *remoteNode = new RemoteNode(node);
    remoteNode->setWeakFlag(false);
    nodes->addNode(remoteNode);
  }
  
  nodeGraph->unlock();

  return true;
}

////////////////////////////////////////////////
// Execution
////////////////////////////////////////////////

bool Round::LocalNode::setError(int rpcErrorCode, Error *err) {
  if (!err)
    return false;
  RPC::JSON::ErrorCodeToError(rpcErrorCode, err);
  return true;
}

bool Round::LocalNode::execMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  if (!nodeReq || !nodeRes || !error)
    return false;
  
  // Check dest
  
  if (!nodeReq->isDestValid()) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
    return false;
  }
  
  bool isDestHash = nodeReq->isDestHash();
  if (isDestHash) {
    std::string nodeHash;
    if (nodeReq->getDest(&nodeHash)) {
      NodeGraph *nodeGraph = getNodeGraph();
      if (!nodeGraph->isHandleNode(this, nodeHash)) {
        setError(RPC::JSON::ErrorCodeMovedPermanently, error);
        return false;
      }
    }
  }
  
  // Update local clock
  
  clock_t remoteTs;
  if (nodeRes->getTimestamp(&remoteTs)) {
    setRemoteClock(remoteTs);
  }
  else {
    incrementLocalClock();
  }
  
  // Exec Method (One node)

  bool isDestOne = nodeReq->isDestOne();
  if (isDestOne) {
    return execMethod(nodeReq, nodeRes, error);
  }
  
  // Exec Method (Multi node)

  JSONArray *batchArray = new JSONArray();
  nodeRes->setResult(batchArray);
  
  Error thisNodeError;
  NodeResponse *thisNodeRes = new NodeResponse();
  execMethod(nodeReq, thisNodeRes, &thisNodeError);
  thisNodeRes->setDest(this);
  batchArray->add(thisNodeRes);
  
  NodeList otherNodes;
  if (nodeReq->isDestAll()) {
    getAllOtherNodes(&otherNodes);
  }
  else if (nodeReq->hasQuorum()) {
    size_t quorum;
    if (nodeReq->getQuorum(&quorum)) {
      getQuorumNodes(&otherNodes, quorum);
    }
  }
  for (NodeList::iterator node = otherNodes.begin(); node != otherNodes.end(); node++) {
    Error otherNodeError;
    NodeResponse *otherNodeRes = new NodeResponse();
    (*node)->postMessage(nodeReq, otherNodeRes, &otherNodeError);
    otherNodeRes->setDest((*node));
    batchArray->add(otherNodeRes);
  }

  return true;
}

bool Round::LocalNode::execMessage(const NodeBatchRequest *nodeBatchReq, NodeBatchResponse *nodeBatchRes, Error *error) {
  for (NodeBatchRequest::const_iterator jsonObj = nodeBatchReq->begin(); jsonObj != nodeBatchReq->end(); jsonObj++) {
    const NodeRequest *nodeReq = (dynamic_cast<NodeRequest *>(*jsonObj));
    if (!nodeReq)
      continue;
    NodeResponse *nodeRes = new NodeResponse();
    execMessage(nodeReq, nodeRes, error);
    nodeBatchRes->add(nodeRes);
  }
  return true;
}

////////////////////////////////////////////////
// Dynamic Method
////////////////////////////////////////////////

bool Round::LocalNode::isDynamicMethod(const std::string &method) {
  return this->scriptMgr.hasScript(method);
}

bool Round::LocalNode::execDynamicMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string method;
  nodeReq->getMethod(&method);
  
  if (!this->scriptMgr.hasScript(method)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  std::string params;
  nodeReq->getParams(&params);
  
  std::string result;
  bool isSuccess = this->scriptMgr.execMethod(method, params, &result, error);
  if (isSuccess) {
    nodeRes->setResult(result);
  }
  else {
    nodeRes->setError(error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Static Method
////////////////////////////////////////////////

bool Round::LocalNode::isStaticMethod(const std::string &method) {
  return this->staticMethodMgr.hasMethod(method);
}

bool Round::LocalNode::execStaticMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (!this->staticMethodMgr.hasMethod(reqMethod)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  bool isSuccess = this->staticMethodMgr.exec(reqMethod, this, nodeReq, nodeRes);
  if (!isSuccess) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Native Method
////////////////////////////////////////////////

bool Round::LocalNode::isNativeMethod(const std::string &method) {
  return this->sysMethodMgr.hasMethod(method);
}

bool Round::LocalNode::execNativeMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  std::string reqMethod;
  nodeReq->getMethod(&reqMethod);
  
  if (!this->sysMethodMgr.hasMethod(reqMethod)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  bool isSuccess = this->sysMethodMgr.exec(reqMethod, this, nodeReq, nodeRes);
  if (!isSuccess) {
    setError(RPC::JSON::ErrorCodeInvalidParams, error);
  }
  
  return isSuccess;
}

////////////////////////////////////////////////
// Alias Method
////////////////////////////////////////////////

bool Round::LocalNode::isAliasMethod(const std::string &method) {
  this->aliasMgr.lock();
  bool isAlias = this->aliasMgr.hasAlias(method);
  this->aliasMgr.unlock();
  return isAlias;
}

bool Round::LocalNode::execAliasMethod(const NodeRequest *aliasReq, NodeResponse *nodeRes, Error *error) {
  std::string reqMethod;
  aliasReq->getMethod(&reqMethod);
  
  this->aliasMgr.lock();
  
  Alias *alias = this->aliasMgr.findAlias(reqMethod);
  if (!alias) {
    this->aliasMgr.unlock();
    return false;
  }

  std::string sourceMethod;
  if (!alias->getObject(&sourceMethod)) {
    this->aliasMgr.unlock();
    return false;
  }
  
  std::string defaultParams;
  if (!alias->getDefaults(&defaultParams)) {
    this->aliasMgr.unlock();
    return false;
  }
  
  this->aliasMgr.unlock();
  
  NodeRequest nodeReq;
  nodeReq.setParamsWithDefault(aliasReq, defaultParams);
  nodeReq.setMethod(sourceMethod);
  
  return execMethod(&nodeReq, nodeRes, error);
}

////////////////////////////////////////////////
// Exce Method
////////////////////////////////////////////////

bool Round::LocalNode::execMethod(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) {
  // Set id and ts parameter
  
  size_t msgId;
  if (nodeReq->getId(&msgId)) {
    nodeRes->setId(msgId);
  }
  nodeRes->setTimestamp(getLocalClock());
  
  // Exec Message
  
  std::string name;
  if (!nodeReq->getMethod(&name) || (name.length() <= 0)) {
    setError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }
  
  bool isMethodExecuted = false;
  bool isMethodSuccess = false;
  
  if (isStaticMethod(name)) {
    isMethodExecuted = true;
    isMethodSuccess = execStaticMethod(nodeReq, nodeRes, error);
  }
  
  if (isDynamicMethod(name)) {
    isMethodExecuted = true;
    isMethodSuccess = execDynamicMethod(nodeReq, nodeRes, error);
  }
  
  if (isNativeMethod(name)) {
    isMethodExecuted = true;
    isMethodSuccess = execNativeMethod(nodeReq, nodeRes, error);
  }

  if (isAliasMethod(name)) {
    isMethodExecuted = true;
    isMethodSuccess = execAliasMethod(nodeReq, nodeRes, error);
  }
  
  if (!isMethodExecuted) {
    setError(RPC::JSON::ErrorCodeMethodNotFound, error);
    return false;
  }

  if (!isMethodSuccess)
    return false;
  
  if (!hasRoute(name))
    return true;
  
  NodeResponse routeNodeRes;
  if (!execRoute(name, nodeRes, &routeNodeRes, error))
    return false;
  
  nodeRes->set(&routeNodeRes);
  
  return true;
}

////////////////////////////////////////////////
// Exec Route
////////////////////////////////////////////////

bool Round::LocalNode::hasRoute(const std::string &name) {
  this->routeMgr.lock();

  bool hasRoute = this->routeMgr.hasRoute(name);
  
  this->routeMgr.unlock();

  return hasRoute;
}

bool Round::LocalNode::execRoute(const std::string &name, const NodeResponse *prevNodeRes, NodeResponse *nodeRes, Error *error) {
  this->routeMgr.lock();
  
  RouteList *routeList = this->routeMgr.getRouteList(name);
  if (!routeList) {
    this->routeMgr.unlock();
    return false;
  }

  std::string params;
  prevNodeRes->getResult(&params);
  
  // Set prev response if all route types are event.
  nodeRes->setResult(params);
  
  bool isSuccess = true;
  
  for (RouteList::const_iterator routeIt = routeList->begin(); routeIt != routeList->end(); routeIt++) {
    Route *route = *routeIt;
    
    // TODO Check cluser.node too.
    std::string target;
    if (!route->getDestinationTarget(&target))
      continue;
    
    NodeRequest nodeReq;
    nodeReq.setMethod(target);
    nodeReq.setParams(params);

    if (route->isEvent()) {
      NodeResponse eventRes;
      if (!execMethod(&nodeReq, &eventRes, error)) {
        isSuccess = false;
      }
    }
    else if (route->isPipe()) {
      if (!execMethod(&nodeReq, nodeRes, error)) {
        isSuccess = false;
      }
    }
  }
  
  this->routeMgr.unlock();
  
  
  return isSuccess;
}

////////////////////////////////////////////////
// Exec Trigger
////////////////////////////////////////////////

bool Round::LocalNode::execTrigger(const std::string &name, Error *error) {
  return false;
}
