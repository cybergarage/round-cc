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

////////////////////////////////////////
// SystemMethodResponse
////////////////////////////////////////

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;  
  this->nodeRes->setVersion(RPC::JSON::VERSION);
}

////////////////////////////////////////
// SystemGetClusterInfoResponse
////////////////////////////////////////

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
  SystemGetClusterInfoResponse sysRes(nodeRes);
  JSONDictionary *clusterDict = sysRes.getResultClusterDict();
  SystemClusterInfoDict clusterInfoDict(clusterDict);
  return clusterInfoDict.setCluster(node);
}

bool Round::SystemGetClusterInfoResponse::getCluster(Cluster *cluster) {
  JSONDictionary *clusterDict = getResultClusterDict();
  SystemClusterInfoDict clusterInfoDict(clusterDict);
  return clusterInfoDict.getCluster(cluster);
  return true;
}

////////////////////////////////////////
// SystemGetNetworkInfoResponse
////////////////////////////////////////

Round::JSONDictionary *Round::SystemGetNetworkInfoResponse::getResultClustersDict() {
  JSONDictionary *resultDict = this->nodeRes->getResultDict();
  if (!resultDict)
    return NULL;
  
  JSONObject *jsonObj = NULL;
  resultDict->get(CLUSTERS, &jsonObj);
  
  JSONDictionary *clusterDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (clusterDict)
    return clusterDict;
  
  clusterDict = new JSONDictionary();
  resultDict->set(CLUSTERS, clusterDict);
  
  return clusterDict;
}

Round::JSONArray *Round::SystemGetNetworkInfoResponse::getResultClustersArray() {
  JSONDictionary *clustersDict = getResultClustersDict();
  if (!clustersDict)
    return NULL;
  
  JSONObject *jsonObj = NULL;
  clustersDict->get(NODES, &jsonObj);
  
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  clustersDict->set(NODES, jsonArray);
  
  return jsonArray;
}

bool Round::SystemGetNetworkInfoResponse::setClusters(LocalNode *node) {

  // Cluseter Nodes
  
  JSONArray *clusterArray = getResultClustersArray();
  
  const NodeGraph *nodeGraph = node->getNodeGraph();
  size_t nodeCnt = nodeGraph->size();
  for (size_t n=0; n<nodeCnt; n++) {
    
    Node *node = nodeGraph->getNode(n);
    if (!node)
      continue;
    
    JSONDictionary *jsonDict = new JSONDictionary();
    SystemNodeInfoDict nodeInfo(jsonDict);
    nodeInfo.setNode(node);
    
    clusterArray->add(jsonDict);
  }
  
  return true;
}

bool Round::SystemGetNetworkInfoResponse::getClusters(ClusterList *clusterList) {
  return false;
}
