/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTSERVER_H_
#define _ROUNDCC_TESTSERVER_H_

#include <boost/test/unit_test.hpp>
#include <round/Round.h>
#include <round/common/Random.h>

class TestServer : public Round::Server {
 public:
  TestServer() {
  }
};

#endif
