/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/common/Operation.h>

long Round::OperationManager::LOOP_WAIT_TIME = 500;

Round::OperationManager::OperationManager() {
  setLoopWaitTime(LOOP_WAIT_TIME);
  setErrorHandler(NULL);
}

Round::OperationManager::~OperationManager() {
}

void Round::OperationManager::run() {
  while (isRunnable()) {
    if (!this->queue.hasOperations()) {
      sleep(getLoopWaitTime());
      continue;
    }
    
    Operation *operation = this->queue.nextOperation();
    if (!operation)
      continue;
    
    Error error;
    if (!operation->execute(&error)) {
      if (this->errorHandler) {
        this->errorHandler->operationErrorOccurred(operation, &error);
      }
    }
    delete operation;
  }
}
