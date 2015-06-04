/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <complex>
#include <round/common/ConsistentHash.h>

Round::ConsistentHashGraph::ConsistentHashGraph() {
}

Round::ConsistentHashGraph::~ConsistentHashGraph() {
}

void Round::ConsistentHashGraph::lock() const {
  this->mutex.lock();
}

void Round::ConsistentHashGraph::unlock() const {
  this->mutex.unlock();
}

bool Round::ConsistentHashGraph::hasNode(const ConsistentHashNode *targetNode) const {
  return (0 <= getNodeIndex(targetNode)) ? true : false;
}

bool Round::ConsistentHashGraph::isLastNode(const ConsistentHashNode *targetNode) const {
  size_t nodeIdx = getNodeIndex(targetNode);
  return (nodeIdx == (size()-1));
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getLastNode() const {
  if (size() <= 0)
    return NULL;
  return at(size()-1);
}

bool Round::ConsistentHashGraph::addNode(ConsistentHashNode *newNode) {
  if (hasNode(newNode))
    return false;
  
  lock();

  Round::ConsistentHashGraph::iterator insertIndex = begin();
  for (Round::ConsistentHashGraph::reverse_iterator node = rbegin(); node != rend(); node++) {
    int compareResult = (*node)->compare(newNode);
    if (compareResult < 0) {
      insertIndex = node.base();
      break;
    }
  }

  insert(insertIndex, newNode);

  unlock();

  return true;
}

bool Round::ConsistentHashGraph::removeNode(const ConsistentHashNode *targetNode) {
  ssize_t nodeIdx = getNodeIndex(targetNode);
  if (nodeIdx < 0)
    return false;

  lock();

  erase(begin() + nodeIdx);

  unlock();

  return true;
}

ssize_t Round::ConsistentHashGraph::getNodeIndex(const ConsistentHashNode *targetNode) const {
  ssize_t nodeIdx = -1;

  std::string targetNodeHashCode;
  if (targetNode->getHashCode(&targetNodeHashCode) == false)
    return nodeIdx;

  lock();

  for (Round::ConsistentHashGraph::const_iterator node = begin(); node != end(); node++) {
    std::string nodeHashCode;
    if ((*node)->getHashCode(&nodeHashCode) == false)
      continue;
    if (targetNodeHashCode.compare(nodeHashCode) == 0) {
      nodeIdx = node - begin();
      break;
    }
  }

  unlock();

  return nodeIdx;
}

off_t Round::ConsistentHashGraph::getForwardNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const {
  size_t nodeCount = size();
  ssize_t firstNodeIndex = getNodeIndex(firstNode);
  ssize_t lastNodeIndex = getNodeIndex(lastNode);
  
  if (firstNodeIndex < 0)
    return 0;
  if (lastNodeIndex < 0)
    return 0;
  
  off_t clockwiseOffset;
  if (firstNodeIndex == lastNodeIndex) {
    clockwiseOffset = 0;
  }
  else if (firstNodeIndex <= lastNodeIndex) {
    clockwiseOffset = lastNodeIndex - firstNodeIndex;
  }
  else {
    clockwiseOffset = (lastNodeIndex + nodeCount) - firstNodeIndex;
  }
  
  return clockwiseOffset;
}

off_t Round::ConsistentHashGraph::getBackwardNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const {
  size_t nodeCount = size();
  ssize_t firstNodeIndex = getNodeIndex(firstNode);
  ssize_t lastNodeIndex = getNodeIndex(lastNode);
  
  if (firstNodeIndex < 0)
    return 0;
  if (lastNodeIndex < 0)
    return 0;
  
  off_t counterClockwiseOffset;
  if (firstNodeIndex == lastNodeIndex) {
    counterClockwiseOffset = 0;
  }
  else if (firstNodeIndex <= lastNodeIndex) {
    counterClockwiseOffset = lastNodeIndex - (firstNodeIndex + nodeCount);
  }
  else {
    counterClockwiseOffset = lastNodeIndex - firstNodeIndex;
  }
  
  return counterClockwiseOffset;
}

off_t Round::ConsistentHashGraph::getMinNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const {
  off_t clockwiseOffset = getForwardNodeDistance(firstNode, lastNode);
  off_t counterClockwiseOffset = getBackwardNodeDistance(firstNode, lastNode);
  return (std::abs(clockwiseOffset) < std::abs(counterClockwiseOffset)) ? clockwiseOffset : counterClockwiseOffset;
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getHandleNode(const std::string &hashCode) const {
  ConsistentHashNode *hadleNode = NULL;
  
  lock();
  
  for (Round::ConsistentHashGraph::const_iterator node = begin(); node != end(); node++) {
    Round::ConsistentHashGraph::const_iterator nextNode = node + 1;
    if (nextNode == end())
      break;
    std::string nodeHashCode;
    std::string nextNodeHashCode;
    if ((*node)->getHashCode(&nodeHashCode) == false)
      continue;
    if ((*nextNode)->getHashCode(&nextNodeHashCode) == false)
      continue;
    if ((nodeHashCode <= hashCode) && (hashCode < nextNodeHashCode)) {
      hadleNode = *node;
      break;
    }
  }
  
  if (!hadleNode && (0 < size()))
    hadleNode = at(size()-1);
  
  unlock();
  
  return hadleNode;
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getHandleNode(const Round::ConsistentHashObject *hashObject) const {
  std::string hashCode;
  if (!hashObject->getHashCode(&hashCode))
    return NULL;  
  return getHandleNode(hashCode);
}

bool Round::ConsistentHashGraph::isHandleNode(const ConsistentHashNode *hashNode, const std::string &hashCode) const {
  return (hashNode == getHandleNode(hashCode)) ? true : false;
}

bool Round::ConsistentHashGraph::isHandleNode(const ConsistentHashNode *hashNode, const ConsistentHashObject *hashObject) const {
  return (hashNode == getHandleNode(hashObject)) ? true : false;
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getOffsetNode(const ConsistentHashNode *node, off_t offset) const {
  ssize_t nodeIndex = getNodeIndex(node);
  if (nodeIndex < 0)
    return NULL;

  ssize_t nodeCount = size();
  
  ssize_t offsetNodeIndex = nodeIndex + offset;
  if (offsetNodeIndex < 0) {
    while (offsetNodeIndex < 0) {
      offsetNodeIndex += nodeCount;
    }
    offsetNodeIndex = offsetNodeIndex % nodeCount;
  }
  offsetNodeIndex = offsetNodeIndex % nodeCount;
  
  ConsistentHashNode *hadleNode = NULL;

  lock();

  hadleNode = at(offsetNodeIndex);

  unlock();

  return hadleNode;
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getNextNode(const ConsistentHashNode *node) const {
  return getOffsetNode(node, 1);
}

Round::ConsistentHashNode *Round::ConsistentHashGraph::getPrevNode(const ConsistentHashNode *node) const {
  return getOffsetNode(node, -1);
}

