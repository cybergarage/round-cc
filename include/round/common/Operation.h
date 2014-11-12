/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_OPERATION_H_
#define _ROUNDCC_OPERATION_H_

#include <queue>

#include <round/common/Error.h>
#include <round/common/Thread.h>

namespace Round {

class Operation {
public:
  
  Operation();
  virtual ~Operation();
  
  virtual bool execute(Error *error) = 0;
};

class OperationQueue : private std::queue<Operation *> {
 public:
  
  OperationQueue();
  ~OperationQueue();

  bool addOperation(Operation *operation);
  bool hasOperations();
  Operation *nextOperation();

 private:
  
  bool clear();
};

class OperationErrorHander {
public:
  virtual void operationErrorOccurred(const Operation *operation, const Error *error) = 0;
};

class OperationManager : public ThreadCore {
public:
  
  static long LOOP_WAIT_TIME;
  
  OperationManager();
  ~OperationManager();

  void setLoopWaitTime(long value) {
    this->loopWaitTime = value;
  }
  
  long getLoopWaitTime() {
    return this->loopWaitTime;
  }

  void setErrorHandler(OperationErrorHander *handler) {
    this->errorHandler = handler;
  }
  
  OperationErrorHander *getErrorHandler() {
    return this->errorHandler;
  }
  
  bool addOperation(Operation *operation) {
    return this->queue.addOperation(operation);
  }

  void run();
  
private:
  
  OperationQueue queue;
  long loopWaitTime;
  OperationErrorHander *errorHandler;

};
  
}

#endif
