/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/local/method/SystemMethod.h>

const std::string Round::SystemNodeInfoDict::NAME     = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::SystemNodeInfoDict::ADDR     = ROUNDCC_SYSTEM_METHOD_PARAM_ADDR;
const std::string Round::SystemNodeInfoDict::PORT     = ROUNDCC_SYSTEM_METHOD_PARAM_PORT;
const std::string Round::SystemNodeInfoDict::HASH     = ROUNDCC_SYSTEM_METHOD_PARAM_HASH;
const std::string Round::SystemNodeInfoDict::VER      = ROUNDCC_SYSTEM_METHOD_PARAM_VERSION;
const std::string Round::SystemNodeInfoDict::CLUSTER  = ROUNDCC_SYSTEM_METHOD_PARAM_CLUSTER;
const std::string Round::SystemNodeInfoDict::STATE    = ROUNDCC_SYSTEM_METHOD_PARAM_STATE;

bool Round::SystemNodeInfoDict::setNode(Node *node) {
  Error error;
  
  std::string nodeAddr;
  if (!node->getRequestAddress(&nodeAddr, &error)) {
    return false;
  }
  
  int nodePort;
  if (!node->getRequestPort(&nodePort, &error)) {
    return false;
  }
  
  std::string nodeCluster;
  if (!node->getClusterName(&nodeCluster, &error)) {
    return false;
  }
  
  std::string nodeHash;
  if (!node->getHashCode(&nodeHash)) {
    return false;
  }
  
  setAddress(nodeAddr);
  setPort(nodePort);
  setCluster(nodeCluster);
  setHash(nodeHash);

  LocalNode *localNode = dynamic_cast<LocalNode *>(node);
  if (localNode) {
    std::string stateString = localNode->getStateString();
    setState(stateString);
  };

  return true;
}

bool Round::SystemNodeInfoDict::getNode(RemoteNode *node) {
  std::string nodeAddr;
  if (!getAddress(&nodeAddr)) {
    return false;
  }
  int nodePort;
  if (!getPort(&nodePort)) {
    return false;
  }
  
  std::string nodeCluster;
  if (!getCluster(&nodeCluster)) {
    return false;
  }
  
  node->setRequestAddress(nodeAddr);
  node->setRequestPort(nodePort);
  node->setClusterName(nodeCluster);
  
  return true;
}
