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

Round::NodeList::NodeList() {
}

Round::NodeList::~NodeList() {
}

void Round::NodeList::set(const NodeList *nodeList) {
  clear();
  for (NodeList::const_iterator node = nodeList->begin(); node != nodeList->end(); node++) {
    addNode(*node);
  }
}
