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

#include <string.h>
#include <round/common/Error.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(ErroSetterTest01) {
  Error err01(1);
  BOOST_CHECK_EQUAL(err01.getCode(), 1);

  Error err02;
  BOOST_CHECK_EQUAL(err02.getCode(), 0);
  err02.setCode(1);
  BOOST_CHECK_EQUAL(err02.getCode(), 1);
}

BOOST_AUTO_TEST_CASE(ErroSetterTest02) {
  Error err01(2, "error");
  BOOST_CHECK_EQUAL(err01.getCode(), 2);
  BOOST_CHECK_EQUAL(strcmp("error", err01.getMessage()), 0);

  Error err02;
  BOOST_CHECK_EQUAL(err02.getCode(), 0);
  err02.setCode(2);
  err02.setMessage("error");
  BOOST_CHECK_EQUAL(err02.getCode(), 2);
  BOOST_CHECK_EQUAL(strcmp("error", err02.getMessage()), 0);
}

BOOST_AUTO_TEST_CASE(ErroDetailSetterTest) {
  Error err;
  BOOST_CHECK_EQUAL(err.getDetailCode(), 0);
  
  err.setCode(1);
  err.setDetailCode(100);
  BOOST_CHECK_EQUAL(err.getDetailCode(), 100);
  BOOST_CHECK(err.getDetailCode() != err.getCode());

  err.setMessage("error");
  err.setDetailMessage("detail error");
  BOOST_CHECK(strcmp("detail error", err.getDetailMessage()) == 0);
  BOOST_CHECK(strcmp(err.getMessage(), err.getDetailMessage()) != 0);
}

BOOST_AUTO_TEST_CASE(ErroCopyTest) {
  Error err01(2, "error");
  Error err02 = err01;

  BOOST_CHECK(err01.equals(err02));
}

BOOST_AUTO_TEST_SUITE_END()
