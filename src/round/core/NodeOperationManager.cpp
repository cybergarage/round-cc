/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/core/NodeOperation.h>

long Round::NodeOperationManager::DEFALUT_LOOP_WAIT_TIME = 500;

Round::NodeOperationManager::NodeOperationManager() {
  setLoopWaitTime(DEFALUT_LOOP_WAIT_TIME);
  setErrorHandler(this);
}

Round::NodeOperationManager::~NodeOperationManager() {
}

void Round::NodeOperationManager::operationErrorOccurred(const Operation *ope, const Error *error) {
  if (!this->nodeErrorHandler)
    return;
  const NodeOperation *nodeOpe = dynamic_cast<const NodeOperation *>(ope);
  if (!nodeOpe)
    return;
  this->nodeErrorHandler->nodeOperationErrorOccurred(nodeOpe, error);
}
