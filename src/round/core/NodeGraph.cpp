/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Node.h>
#include <round/core/NodeGraph.h>
#include <round/common/Random.h>

Round::NodeGraph::NodeGraph() {
}

Round::NodeGraph::~NodeGraph() {
  clear();
}

bool Round::NodeGraph::set(const NodeGraph &otherNodeGraph) {
  clear();
  
  bool areAllNodesAdded = true;
  size_t otherNodeCount = otherNodeGraph.size();
  for (size_t n=0; n<otherNodeCount; n++) {
    Node *node = otherNodeGraph.getNode(n);
    Node *newNode = node;
    if (node->isCloneable())
      newNode = node->clone();
    bool isAdded = ConsistentHashGraph::addNode(newNode);
    if (!isAdded) {
      areAllNodesAdded = false;
      if (node->isCloneable())
        delete newNode;
    }
  }
  return areAllNodesAdded;
}

bool Round::NodeGraph::addNode(Round::Node *node) {
  Node *newNode = node;
  if (node->isCloneable()) {
    newNode = node->clone();
    newNode->setWeakFlag(false);
  }
  bool isAdded = ConsistentHashGraph::addNode(newNode);
  if (!isAdded) {
    if (node->isCloneable())
      delete newNode;
  }
  return isAdded;
}

bool Round::NodeGraph::removeNode(const Round::Node *node) {
  return ConsistentHashGraph::removeNode(node);
}

Round::Node *Round::NodeGraph::getNode(size_t index) const {
  if (size() < (index+1))
    return NULL;
  return static_cast<Node *>(ConsistentHashGraph::at(index));
}

Round::Node *Round::NodeGraph::getRandomNode() const {
  int nodeSize = (int)size();
  Random nodeIdx(0, (nodeSize-1));
  return getNode(nodeIdx.rand());
}

Round::Node *Round::NodeGraph::getNodeByHashCode(const std::string &hashCode) const {
  for (NodeGraph::const_iterator content = begin(); content != end(); content++) {
    Node *node = static_cast<Node *>(*content);
    if (!node)
      continue;
    std::string nodeHash;
    if (!node->getHashCode(&nodeHash))
      continue;
    if (hashCode.compare(nodeHash) == 0)
      return node;
  }
  return NULL;
}

bool Round::NodeGraph::hasNode(const Round::Node *node) const {
  return ConsistentHashGraph::hasNode(node);
}

bool Round::NodeGraph::isLeaderNode(const Node *node) const {
  return ConsistentHashGraph::isLastNode(node);
}

Round::Node *Round::NodeGraph::getOffsetNode(const Node *node, off_t offset) const {
  return static_cast<Node *>(ConsistentHashGraph::getOffsetNode(node, offset));
}

Round::Node *Round::NodeGraph::getNextNode(const Node *node) const {
  return static_cast<Node *>(ConsistentHashGraph::getNextNode(node));
}

Round::Node *Round::NodeGraph::getPrevNode(const Node *node) const {
  return static_cast<Node *>(ConsistentHashGraph::getPrevNode(node));
}

bool Round::NodeGraph::clear() {
  for (NodeGraph::iterator content = begin(); content != end(); content++) {
    Node *node = static_cast<Node *>(*content);
    if (!node)
      continue;
    if (node->isWeak())
      continue;
    delete node;
  }
  ConsistentHashGraph::clear();
  return true;
}

std::size_t Round::NodeGraph::size() const {
  return ConsistentHashGraph::size();
}
