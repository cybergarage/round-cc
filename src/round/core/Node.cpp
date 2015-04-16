/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/lexical_cast.hpp>

#include <round/Round.h>
#include <round/core/Node.h>
#include <round/core/local/method/SystemMethod.h>

const std::string Round::Node::NAME = ROUNDCC_PRODUCT_NAME;
const std::string Round::Node::VER= ROUNDCC_PRODUCT_VERSION;

Round::Node::Node() {
  setWeakFlag(true);
}

Round::Node::~Node() {
}

bool Round::Node::isAlive(Error *error) {
  std::string currClockStr = boost::lexical_cast<std::string>(getLocalClock());
  SystemEchoRequest nodeReq;
  nodeReq.setParams(currClockStr);
  
  NodeResponse nodeRes;
  if (!postMessage(&nodeReq, &nodeRes, error))
    return false;

  std::string echoResult;
  if (!nodeRes.getResult(&echoResult))
    return false;
  
  return (currClockStr.compare(echoResult) == 0) ? true : false;
}

bool Round::Node::isLeader(Error *error) {
  Cluster cluster;
  if (!getCluster(&cluster, error))
    return false;
  return cluster.isLeaderNode(this);
}

bool Round::Node::getStatus(NodeStatus *status, Error *error) {
  // TODO Not yet implemented
  return false;
}

bool Round::Node::getCluster(Cluster *cluster, Error *error) {
  SystemGetClusterInfoRequest nodeReq;
  NodeResponse nodeRes;
  if (!postMessage(&nodeReq, &nodeRes, error))
    return false;  
  SystemGetClusterInfoResponse sysRes(&nodeRes);
  return sysRes.getCluster(cluster);
}

bool Round::Node::getClusterList(ClusterList *clusterList, Error *error) {
  SystemGetNetworkInfoRequest nodeReq;
  NodeResponse nodeRes;
  if (!postMessage(&nodeReq, &nodeRes, error))
    return false;
  SystemGetNetworkInfoResponse sysRes(&nodeRes);
  return sysRes.getClusters(clusterList);
}

bool Round::Node::findNode(const std::string &nodeHash, Node **node, Error *error) {
  Cluster cluster;
  if (!getCluster(&cluster, error))
    return false;
  *node = cluster.getNodeByHashCode(nodeHash);
  if (!node) {
    // TODO Set error code
    return false;
  }
  return true;
}

bool Round::Node::setRegistry(const std::string &key, const std::string &value, Error *error) {
  SystemSetRegistryRequest nodeReq;
  nodeReq.setKey(key);
  nodeReq.setValue(value);
  
  NodeResponse nodeRes;
  return postMessage(&nodeReq, &nodeRes, error);
}

bool Round::Node::getRegistry(const std::string &key, std::string *value, Error *error) {
  SystemGetRegistryRequest nodeReq;
  nodeReq.setKey(key);
  
  NodeResponse nodeRes;
  if (!postMessage(&nodeReq, &nodeRes, error))
    return false;
  
  return nodeRes.getResult(value);
}

bool Round::Node::setRegistry(const Registry reg, Error *error) {
  return false;
}

bool Round::Node::getRegistry(const std::string &key, Registry *reg, Error *error) {
  return false;
}
