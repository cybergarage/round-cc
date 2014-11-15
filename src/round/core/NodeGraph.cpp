/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Node.h>
#include <round/core/NodeGraph.h>

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
  if (node->isCloneable())
    newNode = node->clone();
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
  return static_cast<Node *>(ConsistentHashGraph::at(index));
}

bool Round::NodeGraph::hasNode(const Round::Node *node) const {
  return ConsistentHashGraph::hasNode(node);
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

void Round::NodeGraph::clear() {
  // FIXME
  /*
  for (NodeGraph::iterator content = begin(); content != end(); content++) {
    Node *node = static_cast<Node *>(*content);
    if (!node)
      continue;
    if (node->isWeak())
      continue;
    delete node;
  }
  */
  ConsistentHashGraph::clear();
}

std::size_t Round::NodeGraph::size() const {
  return ConsistentHashGraph::size();
}
