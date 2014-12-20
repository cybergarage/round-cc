/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/SystemMethod.h>

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
  
  setIp(nodeAddr);
  setPort(nodePort);
  setCluster(nodeCluster);
  setHash(nodeHash);
  
  return true;
}

bool Round::SystemNodeInfoDict::getNode(RemoteNode *node) {
  std::string nodeAddr;
  if (!getIp(&nodeAddr)) {
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
