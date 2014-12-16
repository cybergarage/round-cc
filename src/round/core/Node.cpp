/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>

#include <round/Round.h>
#include <round/core/Node.h>
#include <round/core/NodeGraph.h>

const std::string Round::Node::NAME = ROUNDCC_PRODUCT_NAME;
const std::string Round::Node::VER= ROUNDCC_VERSION;

Round::Node::Node() {
  setWeakFlag(false);
}

Round::Node::~Node() {
}

bool Round::Node::getStatus(NodeStatus *status, Error *error) const {
  return true;
}

bool Round::Node::getCluster(Cluster *cluster, Error *error) const {
  return true;
}

bool Round::Node::getClusterList(ClusterList *clusterList, Error *error) const {
  return true;
}
