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

#include <stdlib.h>
#include <round/common/Random.h>
#include <string.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(RandomTest01) {
  Random rand;

  int randVal = rand.rand();
  BOOST_CHECK(0 <= randVal);
  BOOST_CHECK(randVal <= RAND_MAX);
}

BOOST_AUTO_TEST_CASE(RandomTest02) {
  int minRange = 1;
  int maxRange = 10;

  Random randRange(minRange, maxRange);

  int randVal = randRange.rand();
  BOOST_CHECK(minRange <= randVal);
  BOOST_CHECK(randVal <= maxRange);
}

BOOST_AUTO_TEST_CASE(RandomTest03) {
  int minRange = 10;
  int maxRange = 1;

  Random randRange(minRange, maxRange);
  std::swap(minRange, maxRange);

  int randVal = randRange.rand();
  BOOST_CHECK(minRange <= randVal);
  BOOST_CHECK(randVal <= maxRange);
}

BOOST_AUTO_TEST_CASE(RandomTest04) {
  Random rand;

  int randValue1 = rand.rand();
  int randValue2 = rand.rand();

  int minRange = std::min(randValue1, randValue2);
  int maxRange = std::max(randValue1, randValue2);

  Random randRange(minRange, maxRange);

  int randVal = randRange.rand();
  BOOST_CHECK(minRange <= randVal);
  BOOST_CHECK(randVal <= maxRange);
}

BOOST_AUTO_TEST_CASE(RandomTest05) {
  int minRange = 1;
  int maxRange = 10000000;
  
  Random randRange1(minRange, maxRange);
  Random randRange2(minRange, maxRange);
  
  BOOST_CHECK(randRange1.rand() != randRange2.rand());
  BOOST_CHECK(randRange1.rand() != randRange1.rand());
  BOOST_CHECK(randRange2.rand() != randRange2.rand());
}

BOOST_AUTO_TEST_SUITE_END()

