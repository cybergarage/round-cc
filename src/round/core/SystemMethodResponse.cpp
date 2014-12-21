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

const std::string Round::SystemMethodResponse::NAME     = "name";
const std::string Round::SystemMethodResponse::IP       = "ip";
const std::string Round::SystemMethodResponse::PORT     = "port";
const std::string Round::SystemMethodResponse::HASH     = "hash";
const std::string Round::SystemMethodResponse::VERSION  = "version";
const std::string Round::SystemMethodResponse::CLUSTER  = "cluster";
const std::string Round::SystemMethodResponse::NODES  = "nodes";
const std::string Round::SystemMethodResponse::CLUSTERS = "clusters";

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;  
  this->nodeRes->setVersion(RPC::JSON::VERSION);
}

Round::JSONDictionary *Round::SystemGetClusterInfoResponse::getResultClusterDict() {
  JSONDictionary *resultDict = this->nodeRes->getResultDict();
  if (!resultDict)
    return NULL;
  
  JSONObject *jsonObj = NULL;
  resultDict->get(CLUSTER, &jsonObj);
  
  JSONDictionary *clusterDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (clusterDict)
    return clusterDict;
  
  clusterDict = new JSONDictionary();
  resultDict->set(CLUSTER, clusterDict);
  
  return clusterDict;
}

Round::JSONArray *Round::SystemGetClusterInfoResponse::getResultClusterNodeArray() {
  JSONDictionary *clusterDict = getResultClusterDict();
  if (!clusterDict)
    return NULL;

  JSONObject *jsonObj = NULL;
  clusterDict->get(NODES, &jsonObj);
  
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  clusterDict->set(NODES, jsonArray);
  
  return jsonArray;
}

bool Round::SystemGetClusterInfoResponse::setCluster(LocalNode *node) {
  Error error;
  SystemGetClusterInfoResponse sysRes(nodeRes);
  
  // Cluster Name
  
  JSONDictionary *clusterDict = sysRes.getResultClusterDict();
  std::string clusterName;
  if (node->getClusterName(&clusterName, &error)) {
    clusterDict->set(NAME, clusterName);
  }

  // Cluseter Nodes
  
  JSONArray *clusterNodeArray = sysRes.getResultClusterNodeArray();
  
  const NodeGraph *nodeGraph = node->getNodeGraph();
  size_t nodeCnt = nodeGraph->size();
  for (size_t n=0; n<nodeCnt; n++) {
    
    Node *node = nodeGraph->getNode(n);
    if (!node)
      continue;
    
    JSONDictionary *jsonDict = new JSONDictionary();
    SystemNodeInfoDict nodeInfo(jsonDict);
    nodeInfo.setNode(node);
    
    clusterNodeArray->add(jsonDict);
  }
  
  return true;
}

bool Round::SystemGetClusterInfoResponse::getCluster(Cluster *cluster) {
  
  // Cluster Name
  
  JSONDictionary *clusterDict = getResultClusterDict();
  std::string clusterName;
  if (clusterDict->get(NAME, &clusterName)) {
    cluster->setName(clusterName);
  }
  
  // Cluseter Nodes
  
  JSONArray *clusterNodeArray = getResultClusterNodeArray();
  
  size_t clusterCnt = clusterNodeArray->size();
  for (size_t n=0; n<clusterCnt; n++) {
    JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(clusterNodeArray->getObject(n));
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
