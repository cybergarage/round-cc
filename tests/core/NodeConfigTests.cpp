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

#include <round/core/LocalNode.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

class TestNodeConfig : public LocalConfig {
 public:
  TestNodeConfig() {
  }
};

static const std::string FRACTAL_CONFIG_SAMPLE = \
"; Round Configuration\n" \
"; \n" \
"[node]\n" \
"cluster = round\n" \
"database_dir = /var\n" \
"\n" \
"[httpd]\n" \
"bind_port = 4649\n" \
"bind_address = 127.0.0.1\n" \
"\n" \
"[log]\n" \
"file = /var/log/round.log\n" \
"level = info\n" \
"\n";

BOOST_AUTO_TEST_CASE(RoundNodConfigTest) {
  TestNodeConfig nodeConfig;

  Error err;
  BOOST_CHECK(nodeConfig.loadFromString(FRACTAL_CONFIG_SAMPLE, &err));

  size_t sectionCount = nodeConfig.getSectionCount();
  for (int i = 0; i<sectionCount; i++) {
    size_t sectionKeyCount = nodeConfig.getSectionKeyCount(i);
    for (int j = 0; j<sectionKeyCount; j++) {
      std::string sectionString = nodeConfig.getSectionString(i);
      BOOST_CHECK((0 < sectionString.length()));
      std::string keyString = nodeConfig.getSectionKeyString(i, j);
      BOOST_CHECK((0 < keyString.length()));
    }
  }
}

BOOST_AUTO_TEST_CASE(RoundNodConfigValidTest) {
  TestNodeConfig nodeConfig;
  Error err;
  BOOST_CHECK(!nodeConfig.isValid(&err));
  BOOST_CHECK(nodeConfig.loadFromString(FRACTAL_CONFIG_SAMPLE, &err));
  BOOST_CHECK(nodeConfig.isValid(&err));
}

BOOST_AUTO_TEST_SUITE_END()


