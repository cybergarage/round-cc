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

static const std::string FRACTAL_TEST_SERVER_CONFIG = \
  "; Round Configuration\n" \
  "; \n" \
  "[node]\n" \
  "cluster = round\n" \
  "database_dir = .\n" \
  "\n" \
  "[httpd]\n" \
  "bind_port = 8888\n" \
  "bind_address = auto\n" \
  "\n" \
  "[log]\n" \
  "file = /var/log/round.log\n" \
  "level = info\n" \
  "\n";

class TestServer : public Round::Server {
 public:
  TestServer() {
    Round::Error err;
    BOOST_CHECK(loadConfigFromString(FRACTAL_TEST_SERVER_CONFIG, &err));
    BOOST_CHECK(isConfigValid(&err));
    
    Round::LocalConfig *nodeConfig = getNodeConfig();
    Round::Random httpPortRand(10000, 20000);
    nodeConfig->setHttpdBindPort(httpPortRand.rand());
    
    BOOST_CHECK(isConfigValid(&err));
  }
};

#endif
