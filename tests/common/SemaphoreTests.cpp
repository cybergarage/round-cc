/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/common/Thread.h>
#include <round/common/Semaphore.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(SemaphoreBasicTest) {
  Semaphore *sem = new Semaphore(1);

  BOOST_CHECK_EQUAL(sem->post(), true);
  BOOST_CHECK_EQUAL(sem->wait(), true);

  BOOST_CHECK_EQUAL(sem->post(), true);
  BOOST_CHECK_EQUAL(sem->post(), true);
  BOOST_CHECK_EQUAL(sem->wait(), true);
  BOOST_CHECK_EQUAL(sem->wait(), true);

  BOOST_CHECK_EQUAL(sem->post(), true);
  BOOST_CHECK_EQUAL(sem->wait(), true);
  BOOST_CHECK_EQUAL(sem->post(), true);
  BOOST_CHECK_EQUAL(sem->wait(), true);

  delete sem;
}

BOOST_AUTO_TEST_CASE(SemaphoreMaxCountTest) {
  for (size_t semMaxCount = 1; semMaxCount<10; semMaxCount++) {
    Semaphore sem(semMaxCount);

    for (size_t n=0; n<semMaxCount; n++) {
      BOOST_CHECK_EQUAL(sem.wait(), true);
    }
    
    for (size_t n=0; n<semMaxCount; n++) {
      BOOST_CHECK_EQUAL(sem.post(), true);
    }
  }
}

static const int SEMAPHORE_THREAD_TEST_LOOP_NUM = 10;

class SemaphorePostThread : public Thread<Semaphore> {
 public:
  SemaphorePostThread() {
  }

  void run() {
    Semaphore *sem = getObject();
    for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
      sleep(100);
      BOOST_CHECK_EQUAL(sem->post(), true);
    }
  }
};

BOOST_AUTO_TEST_CASE(SemaphoreThreadTest) {
  Semaphore *sem = new Semaphore(0);
  
  SemaphorePostThread semPostThread;
  semPostThread.setObject(sem);
  BOOST_CHECK(semPostThread.start());
  
  for (int n = 0; n < SEMAPHORE_THREAD_TEST_LOOP_NUM; n++) {
    BOOST_CHECK_EQUAL(sem->wait(), true);
  }
  
  delete sem;
}
