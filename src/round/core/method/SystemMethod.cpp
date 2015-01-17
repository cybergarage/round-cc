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

#include <round/core/Method.h>

////////////////////////////////////////
// SystemNodeInfoDict
////////////////////////////////////////

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

////////////////////////////////////////
// SystemClusterInfoDict
////////////////////////////////////////

Round::JSONArray *Round::SystemClusterInfoDict::getNodeArray() {
  JSONObject *jsonObj = NULL;
  this->jsonDict->get(SystemMethodResponse::NODES, &jsonObj);
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  this->jsonDict->set(SystemMethodResponse::NODES, jsonArray);
  
  return jsonArray;
}

bool Round::SystemClusterInfoDict::setCluster(LocalNode *node) {
  Error error;
  
  // Cluster Name
  
  std::string clusterName;
  if (node->getClusterName(&clusterName, &error)) {
    this->jsonDict->set(SystemMethodResponse::NAME, clusterName);
  }
  
  // Cluseter Nodes
  
  JSONArray *nodeArray = getNodeArray();
  
  const NodeGraph *nodeGraph = node->getNodeGraph();
  size_t nodeCnt = nodeGraph->size();
  for (size_t n=0; n<nodeCnt; n++) {
    
    Node *node = nodeGraph->getNode(n);
    if (!node)
      continue;
    
    JSONDictionary *jsonDict = new JSONDictionary();
    SystemNodeInfoDict nodeInfo(jsonDict);
    nodeInfo.setNode(node);
    
    nodeArray->add(jsonDict);
  }
  
  return true;
}

bool Round::SystemClusterInfoDict::getCluster(Cluster *cluster) {
  // Cluster Name
  
  std::string clusterName;
  if (this->jsonDict->get(SystemMethodResponse::NAME, &clusterName)) {
    cluster->setName(clusterName);
  }
  
  // Cluseter Nodes
  
  JSONArray *nodeArray = getNodeArray();
  
  size_t clusterCnt = nodeArray->size();
  for (size_t n=0; n<clusterCnt; n++) {
    JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(nodeArray->getObject(n));
    if (!jsonDict)
      continue;
    
    RemoteNode *node = new RemoteNode();
    node->setWeakFlag(false);
    
    SystemNodeInfoDict nodeInfoDict(jsonDict);
    if (!nodeInfoDict.getNode(node)) {
      delete node;
      continue;
    }
    
    cluster->addNode(node);
  }
  
  return true;
}

