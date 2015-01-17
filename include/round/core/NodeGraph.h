/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEGRAPH_H_
#define _ROUNDCC_NODEGRAPH_H_

#include <round/common/ConsistentHash.h>

namespace Round {
class Node;

class NodeGraph : public ConsistentHashGraph {
 public:
  NodeGraph();
  ~NodeGraph();

  bool set(const NodeGraph &nodeGraph);
  
  bool addNode(Node *node);
  bool removeNode(const Node *node);

  Node *getNode(size_t index) const;
  std::size_t size() const;

  bool hasNode(const Node *node) const;
  Node *getOffsetNode(const Node *node, off_t offset) const;
  Node *getNextNode(const Node *node) const;
  Node *getPrevNode(const Node *node) const;

  bool clear();
};

}

#endif
