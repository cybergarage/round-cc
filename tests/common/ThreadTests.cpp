/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>
#include <round/common/Thread.h>

#include "RoundTest.h"

using namespace Round;

const int THREAD_TEST_LOOP_NUM = 10;

class TestThread : public Thread<int> {
 public:
  int value;

  TestThread() {
    value = 0;
  }

  void run() {
    for (int n = 0; n < THREAD_TEST_LOOP_NUM; n++)
      value++;
  }
};

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(ThreadTests) {
  TestThread *thread = new TestThread();
  BOOST_CHECK_EQUAL (thread->start(), true);
  while (thread->value != THREAD_TEST_LOOP_NUM)
    Round::Test::Sleep(100);
  BOOST_CHECK_EQUAL(thread->value, THREAD_TEST_LOOP_NUM);
  BOOST_CHECK_EQUAL(thread->stop(), true);
  BOOST_CHECK_EQUAL(thread->stop(), true);
  delete thread;
}

BOOST_AUTO_TEST_CASE(ThreadManagerTests) {
  TestThread *thread = new TestThread();

  ThreadManager threadMgr;
  threadMgr.addThread(thread);
  threadMgr.start();

  while (thread->value != THREAD_TEST_LOOP_NUM)
    Round::Test::Sleep(100);
  
  BOOST_CHECK_EQUAL(thread->value, THREAD_TEST_LOOP_NUM);

  threadMgr.stop();
}

BOOST_AUTO_TEST_SUITE_END()
