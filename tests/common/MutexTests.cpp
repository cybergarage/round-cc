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

#include <round/common/Mutex.h>

using namespace Round;

BOOST_AUTO_TEST_CASE(MutexTests) {
Mutex *mutex = new Mutex();
  BOOST_CHECK_EQUAL(mutex->lock(), true);
  BOOST_CHECK_EQUAL(mutex->unlock(), true);
  delete mutex;
}
