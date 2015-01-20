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
#include <boost/algorithm/string.hpp>

#include <round/common/BitOption.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(RoundBitOptionTest) {
  BitOption bitOpt;

  int testOption = 0x01;

  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), false);

  bitOpt.setOption(testOption, true);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), true);

  bitOpt.setOption(testOption, true);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), true);

  bitOpt.setOption(testOption, false);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), false);

  bitOpt.setOption(testOption, false);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), false);

  bitOpt.setOption(testOption, true);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), true);

  bitOpt.setOption(testOption, true);
  BOOST_CHECK_EQUAL(bitOpt.getOption(testOption), true);
}

BOOST_AUTO_TEST_SUITE_END()
