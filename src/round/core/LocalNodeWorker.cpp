/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>

Round::LocalNodeWorkder::LocalNodeWorkder() {
}

Round::LocalNodeWorkder::~LocalNodeWorkder() {
}

void Round::LocalNodeWorkder::run() {
  LocalNode *node = getObject();
  if (!node)
    return;
  
  while (isRunnable()) {
    const NodeRequest *nodeReq;
    if (!node->waitMessage(&nodeReq))
      break;
    
    if (!nodeReq)
      break;
    
    NodeResponse nodeRes;
    Error err;
    
    node->execMessage(nodeReq, &nodeRes, &err);
    
    delete nodeReq;
  }
}
