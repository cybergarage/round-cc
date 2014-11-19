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

bool Round::Node::getCluster(Cluster *cluster, Error *error) const {
  return true;
}

bool Round::Node::getName(std::string *buffer, Error *error) const {
  return true;
}

bool Round::Node::getVersion(std::string *buffer, Error *error) const {
  return true;
}

bool Round::Node::getStatus(NodeStatus *status, Error *error) const {
  return true;
}

bool Round::Node::getNodeGraph(NodeGraph *nodeGraph, Error *error) {
  return true;
}

bool Round::Node::hasName() const {
  std::string nodeName;
  if (!getName(&nodeName))
    return false;
  return (0 < nodeName.length() ? true : false);
}
