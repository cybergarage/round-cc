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
const std::string Round::SystemMethodResponse::CLUSTERS = "clusters";

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;  
  this->nodeRes->setVersion(RPC::JSON::VERSION);
}

Round::JSONArray *Round::SystemGetClusterInfoResponse::getResultClusterArray() {
  JSONDictionary *resultDict = this->nodeRes->getResultDict();
  if (!resultDict)
    return NULL;

  JSONObject *jsonObj = NULL;
  resultDict->get(CLUSTERS, &jsonObj);
  
  JSONArray *jsonArray = dynamic_cast<JSONArray *>(jsonObj);
  if (jsonArray)
    return jsonArray;
  
  jsonArray = new JSONArray();
  resultDict->set(CLUSTERS, jsonArray);
  
  return jsonArray;
}

bool Round::SystemGetClusterInfoResponse::setCluster(LocalNode *node) {
  SystemGetClusterInfoResponse sysRes(nodeRes);
  
  JSONArray *clusterArray = sysRes.getResultClusterArray();
  
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

bool Round::SystemGetClusterInfoResponse::getCluster(Cluster *cluster) {
  JSONArray *clusterArray = getResultClusterArray();
  
  size_t clusterCnt = clusterArray->size();
  for (size_t n=0; n<clusterCnt; n++) {
    JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(clusterArray->getObject(n));
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
