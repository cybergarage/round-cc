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

const std::string Round::SystemClusterInfoDict::NAME     = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::SystemClusterInfoDict::NODES    = ROUNDCC_SYSTEM_METHOD_PARAM_NODES;
const std::string Round::SystemClusterInfoDict::CLUSTER  = ROUNDCC_SYSTEM_METHOD_PARAM_CLUSTER;

Round::JSONArray *Round::SystemClusterInfoDict::getNodeArray() {
  JSONObject *jsonObj = NULL;
  this->jsonDict->get(NODES, &jsonObj);
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  this->jsonDict->set(NODES, jsonArray);
  
  return jsonArray;
}

bool Round::SystemClusterInfoDict::setCluster(LocalNode *node) {
  Error error;
  
  // Cluster Name
  
  std::string clusterName;
  if (node->getClusterName(&clusterName, &error)) {
    this->jsonDict->set(NAME, clusterName);
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
  if (this->jsonDict->get(NAME, &clusterName)) {
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

