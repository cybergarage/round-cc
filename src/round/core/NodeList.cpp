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

Round::NodeList::NodeList() {
}

Round::NodeList::~NodeList() {
  clear();
}

void Round::NodeList::set(const NodeList *nodeList) {
  clear();
  for (NodeList::const_iterator node = nodeList->begin(); node != nodeList->end(); node++) {
    addNode(*node);
  }
}

void Round::NodeList::clear() {
  for (NodeList::iterator content = begin(); content != end(); content++) {
    Node *node = static_cast<Node *>(*content);
    if (!node)
      continue;
    if (node->isWeak())
      continue;
    delete node;
  }
  std::vector<Node *>::clear();
}
