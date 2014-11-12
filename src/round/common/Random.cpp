/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <algorithm>
#include <boost/random.hpp>

#include <round/common/Random.h>

#if defined(HAVE_BOOST_RANDOM)
static boost::random::mt19937 *gRandEngine = NULL;
#else
static boost::mt19937 *gRandEngine = NULL;
#endif

Round::Random::Random() {
  initialize(0, RAND_MAX);
}

Round::Random::Random(unsigned int min, unsigned int max) {
  initialize(std::min(min, max), std::max(min, max));
}


Round::Random::~Random() {
}

void Round::Random::initialize(unsigned int min, unsigned int max) {
  this->minRange = min;
  this->maxRange = max;
  
  if (!gRandEngine) {
    uint32_t seed = std::time(0) % UINT32_MAX;
#if defined(HAVE_BOOST_RANDOM)
    gRandEngine = new boost::random::mt19937(seed);
#else
    gRandEngine = new boost::mt19937(seed);
#endif
  }
}

unsigned int Round::Random::rand() {
#if defined(HAVE_BOOST_RANDOM)
  boost::random::uniform_int_distribution<> randDist(this->minRange, this->maxRange);
#else
  boost::uniform_smallint<> randDist(this->minRange, this->maxRange);
#endif
  return randDist(*gRandEngine);
}

