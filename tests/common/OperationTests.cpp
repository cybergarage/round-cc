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

#include <round/common/Operation.h>

#include "RoundTest.h"

using namespace std;
using namespace Round;

class TestOperationData : public OperationErrorHander {
public:
  TestOperationData() {
    this->value = 0;
    this->errorCount = 0;
  }
  
  void increment() {
    this->value++;
  }
  
  int getValue() {
    return this->value;
  }
  
  void operationErrorOccurred(const Operation *operation, const Error *error) {
    this->errorCount++;
  }
  
  int getErrorCount() {
    return this->errorCount;
  }
  
private:
  int value;
  int errorCount;
};

class TestOperation : public Operation {
public:
  TestOperation() {
    setData(NULL);
  }

  void setData(TestOperationData *value) {
    this->data = value;
  }
  
  bool execute(Error *error) {
    if (this->data) {
      this->data->increment();
    }
    return true;
  }

private:
  
  TestOperationData *data;
};

class TestErrorOperation : public TestOperation {
public:
  TestErrorOperation() {
    setData(NULL);
  }
  
  bool execute(Error *error) {
    return false;
  }
};


BOOST_AUTO_TEST_CASE(RoundOperationQueueTest) {
  OperationQueue opeQueue;

  const int TEST_OPERATION_COUNT = 10;
  Operation *ope[TEST_OPERATION_COUNT];
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    ope[n] = new TestOperation();
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

BOOST_AUTO_TEST_CASE(RoundOperationManagerLoopWaitTimeTest) {
  const int TEST_OPERATION_WAIT_TIME = 100;
  
  OperationManager opeMgr;
  BOOST_CHECK(0 < opeMgr.getLoopWaitTime());
  opeMgr.setLoopWaitTime(TEST_OPERATION_WAIT_TIME);
  BOOST_CHECK_EQUAL(opeMgr.getLoopWaitTime(), TEST_OPERATION_WAIT_TIME);
  BOOST_CHECK(0 < opeMgr.getLoopWaitTime());
}

BOOST_AUTO_TEST_CASE(RoundOperationManagerTest) {
  const int TEST_OPERATION_COUNT = 10;
  const int TEST_OPERATION_WAIT_TIME = 100;
  
  TestOperationData opeData;
  OperationManager opeMgr;
  opeMgr.setLoopWaitTime(TEST_OPERATION_WAIT_TIME);
  opeMgr.setErrorHandler(&opeData);
  BOOST_CHECK(opeMgr.start());
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    TestOperation *ope = new TestOperation();
    ope->setData(&opeData);
    opeMgr.addOperation(ope);
    Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  }
  Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);

  BOOST_CHECK_EQUAL(opeData.getValue(), TEST_OPERATION_COUNT);
  BOOST_CHECK_EQUAL(opeData.getErrorCount(), 0);
  
  for (int n=0; n<TEST_OPERATION_COUNT; n++) {
    TestErrorOperation *ope = new TestErrorOperation();
    ope->setData(&opeData);
    opeMgr.addOperation(ope);
    Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  }
  Round::Test::Sleep(opeMgr.getLoopWaitTime() * 2);
  
  BOOST_CHECK_EQUAL(opeData.getValue(), TEST_OPERATION_COUNT);
  BOOST_CHECK_EQUAL(opeData.getErrorCount(), TEST_OPERATION_COUNT);
  
  BOOST_CHECK(opeMgr.stop());
}
