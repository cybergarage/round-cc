/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Operation.h>

Round::OperationQueue::OperationQueue() {
}

Round::OperationQueue::~OperationQueue() {
  clear();
}

bool Round::OperationQueue::clear() {
  while (hasOperations()) {
    Operation *operation = nextOperation();
    delete operation;
  }
  return true;
}

bool Round::OperationQueue::addOperation(Operation *operation) {
  push(operation);
  return true;
}

bool Round::OperationQueue::hasOperations() {
  return (0 < size()) ? true : false;
}

Round::Operation *Round::OperationQueue::nextOperation() {
  if (!hasOperations())
    return NULL;
  Operation *op = front();
  pop();
  return op;
}
