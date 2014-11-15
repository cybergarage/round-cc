/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/thread/thread.hpp>

#include <round/core/NodeOperation.h>

#include "RoundTest.h"

using namespace std;
using namespace Round;

class TestNodeOperationData : public NodeOperationErrorHander {
public:
  TestNodeOperationData() {
    this->value = 0;
    this->errorCount = 0;
  }
  
  void increment() {
    this->value++;
  }
  
  int getValue() {
    return this->value;
  }
  
  int getErrorCount() {
    return this->errorCount;
  }

  void nodeOperationErrorOccurred(const NodeOperation *operation, const Error *error) {
    this->errorCount++;
  }

private:
  int value;
  int errorCount;
};

class TestNodeOperation : public NodeOperation {
public:
  TestNodeOperation() {
    setData(NULL);
  }
  
  void setData(TestNodeOperationData *value) {
    this->data = value;
  }
  
  bool execute(Error *error) {
    if (this->data) {
      this->data->increment();
    }
    return true;
  }
  
private:
  
  TestNodeOperationData *data;
};

class TestNodeErrorOperation : public TestNodeOperation {
public:
  TestNodeErrorOperation() {
  }
  
  bool execute(Error *error) {
    return false;
  }
};

BOOST_AUTO_TEST_CASE(RoundNodeOperationQueueTest) {
  OperationQueue opeQueue;
  
  const int TEST_OPERATION_COUNT = 10;
  Operation *ope[TEST_OPERATION_COUNT];
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    ope[n] = new TestNodeOperation();
  }
  
  BOOST_CHECK(!opeQueue.hasOperations());
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    BOOST_CHECK(opeQueue.addOperation(ope[n]));
    BOOST_CHECK(opeQueue.hasOperations());
  }
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    Operation *operation = opeQueue.nextOperation();
    BOOST_CHECK_EQUAL(operation, ope[n]);
  }
  
  BOOST_CHECK(!opeQueue.hasOperations());
}

BOOST_AUTO_TEST_CASE(RoundNodeOperationManagerTest) {
  const int TEST_OPERATION_COUNT = 10;
  const int TEST_OPERATION_WAIT_TIME = 100;
  
  TestNodeOperationData opeData;
  NodeOperationManager opeMgr;
  opeMgr.setLoopWaitTime(TEST_OPERATION_WAIT_TIME);
  opeMgr.setNodeErrorHandler(&opeData);
  BOOST_CHECK(opeMgr.start());
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    TestNodeOperation *ope = new TestNodeOperation();
    ope->setData(&opeData);
    opeMgr.addOperation(ope);
    Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  }
  Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  
  BOOST_CHECK_EQUAL(opeData.getValue(), TEST_OPERATION_COUNT);
  BOOST_CHECK_EQUAL(opeData.getErrorCount(), 0);

  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    TestNodeErrorOperation *ope = new TestNodeErrorOperation();
    ope->setData(&opeData);
    opeMgr.addOperation(ope);
    Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  }
  Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  
  BOOST_CHECK_EQUAL(opeData.getValue(), TEST_OPERATION_COUNT);
  BOOST_CHECK_EQUAL(opeData.getErrorCount(), TEST_OPERATION_COUNT);
  
  BOOST_CHECK(opeMgr.stop());
}
