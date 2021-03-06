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

////////////////////////////////////////
// SystemMethodResponse
////////////////////////////////////////

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;  
  this->nodeRes->setVersion(RPC::JSON::VER);
}

////////////////////////////////////////
// SystemGetClusterInfoResponse
////////////////////////////////////////

const std::string Round::SystemGetClusterInfoResponse::NODES = "nodes";
const std::string Round::SystemGetClusterInfoResponse::CLUSTER = "cluster";

Round::JSONDictionary *Round::SystemGetClusterInfoResponse::getResultClusterDict() {
  JSONDictionary *resultDict = this->nodeRes->getResultDict();
  if (!resultDict)
    return NULL;
  return resultDict->getJSONDictionary(CLUSTER);
}

Round::JSONArray *Round::SystemGetClusterInfoResponse::getResultClusterNodeArray() {
  JSONDictionary *clusterDict = getResultClusterDict();
  if (!clusterDict)
    return NULL;
  return clusterDict->getJSONArray(NODES);
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

const std::string Round::SystemGetNetworkInfoResponse::CLUSTERS = ROUNDCC_SYSTEM_METHOD_PARAM_CLUSTERS;

Round::JSONArray *Round::SystemGetNetworkInfoResponse::getResultClusterArray() {
  JSONDictionary *resultDict = this->nodeRes->getResultDict();
  if (!resultDict)
    return NULL;
  return resultDict->getJSONArray(CLUSTERS);
}

bool Round::SystemGetNetworkInfoResponse::setClusters(LocalNode *node) {
  JSONArray *clusterArray = getResultClusterArray();

  JSONDictionary *jsonDict = new JSONDictionary();
  SystemClusterInfoDict clusterInfoDict(jsonDict);
  clusterInfoDict.setCluster(node);
  
  clusterArray->add(jsonDict);
  
  return true;
}

bool Round::SystemGetNetworkInfoResponse::getClusters(ClusterList *clusterList) {
  JSONArray *clusterArray = getResultClusterArray();
  size_t clusterCnt = clusterArray->size();
  for (size_t n=0; n<clusterCnt; n++) {
    JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(clusterArray->getObject(n));
    if (!jsonDict)
      continue;
    
    SystemClusterInfoDict clusterInfoDict(jsonDict);
    Cluster *cluster = new Cluster();
    if (!clusterInfoDict.getCluster(cluster)) {
      delete cluster;
      continue;
    }
    
    clusterList->addCluster(cluster);
  }
  
  return true;
}
