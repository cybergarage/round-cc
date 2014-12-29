/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_CONSISTENTHASH_H_
#define _ROUNDCC_CONSISTENTHASH_H_

#include <stdlib.h>
#include <vector>
#include <string>

#include <round/common/HashObject.h>
#include <round/common/Mutex.h>

namespace Round {

class ConsistentHashObject : public HashObject {
public:
  
  ConsistentHashObject();
  ~ConsistentHashObject();
};

class ConsistentHashNode : public HashObject {
public:
  
  ConsistentHashNode();
  ~ConsistentHashNode();
};

class ConsistentHashGraph : public std::vector<ConsistentHashNode *> {
 public:
  ConsistentHashGraph();
  ~ConsistentHashGraph();

  bool addNode(ConsistentHashNode *node);
  bool removeNode(const ConsistentHashNode *node);

  bool hasNode(const ConsistentHashNode *node) const;

  ssize_t getNodeIndex(const ConsistentHashNode *node) const;
  
  off_t getForwardNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const;
  off_t getBackwardNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const;
  off_t getMinNodeDistance(const ConsistentHashNode *firstNode, const ConsistentHashNode *lastNode) const;
  
  ConsistentHashNode *getHandleNode(const ConsistentHashObject *hashObject) const;

  ConsistentHashNode *getOffsetNode(const ConsistentHashNode *node, off_t offset) const;
  ConsistentHashNode *getNextNode(const ConsistentHashNode *node) const;
  ConsistentHashNode *getPrevNode(const ConsistentHashNode *node) const;

  void lock() const;
  void unlock() const;

private:

  mutable Mutex mutex;
};

}

#endif
