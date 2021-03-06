/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#define BOOST_TEST_MODULE RoundTest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>

#include <boost/random.hpp>
#include <boost/thread.hpp>

#include <round/core/Log.h>

#include "RoundTest.h"

using namespace std;
using namespace boost;

extern char** environ;

struct RoundFixture {
  RoundFixture() {
    Round::Test::Setup();
  }

  ~RoundFixture() {
  }
};

BOOST_GLOBAL_FIXTURE(RoundFixture);

void Round::Test::Setup() {
  // Setup Log Level
  
  int loggerLevel = LoggerLevel::WARN;
#if defined(ROUND_HAVE_BOOST_UNITTEST_LOGLEVEL)
  boost::unit_test::log_level logLevel = boost::unit_test::runtime_config::log_level();
  if (logLevel <= boost::unit_test::log_level::log_messages) {
    loggerLevel = LoggerLevel::INFO;
    if (logLevel < boost::unit_test::log_level::log_messages)
      loggerLevel = LoggerLevel::TRACE;
  }
#endif
  
  Logger *sharedLogger = Logger::GetSharedInstance();
  sharedLogger->setLevel(loggerLevel);
  sharedLogger->clearAllTargets();
  sharedLogger->addTarget(new LoggerStdoutTarget());
}

int Round::Test::GetRandomRepeatCount(int min, int max) {
#if defined(ROUND_HAVE_BOOST_RANDOM)
  boost::random::mt19937 rndEngine;
  boost::random::uniform_int_distribution<> randDist(min, max);
#else
  boost::mt19937 rndEngine;
  boost::uniform_smallint<> randDist(min, max);
#endif
  return randDist(rndEngine);
}

void Round::Test::Sleep(long milliSecond) {
  boost::this_thread::sleep(boost::posix_time::milliseconds(milliSecond));
}
