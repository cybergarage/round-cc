/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEOPERATION_H_
#define _ROUNDCC_NODEOPERATION_H_

#include <round/common/Error.h>
#include <round/common/Operation.h>

namespace Round {

class NodeOperation : public Operation {
public:
  
  NodeOperation();
  virtual ~NodeOperation();
};

class NodeOperationQueue : public OperationQueue {
 public:
  
  NodeOperationQueue();
  ~NodeOperationQueue();

};

class NodeOperationErrorHander {
  public:
    virtual void nodeOperationErrorOccurred(const NodeOperation *operation, const Error *error) = 0;
};

  
class NodeOperationManager : public OperationManager, public OperationErrorHander {
public:
  
  static long DEFALUT_LOOP_WAIT_TIME;
  
  NodeOperationManager();
  ~NodeOperationManager();

  void setNodeErrorHandler(NodeOperationErrorHander *handler) {
    this->nodeErrorHandler = handler;
  }
  
  NodeOperationErrorHander *getNodeErrorHandler() {
    return this->nodeErrorHandler;
  }

  void operationErrorOccurred(const Operation *operation, const Error *error);

private:
  
  NodeOperationErrorHander *nodeErrorHandler;

};

}

#endif
