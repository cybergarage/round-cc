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

#include <string>
#include <round/common/Config.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

const std::string TEST_CONFIGURATION_NULLLINES= \
"\n" \
"\n" \
"\n" \
"\n" \
"\n" \
"\n";

BOOST_AUTO_TEST_CASE(RoundConfigNullTest) {
  Config config;
  Error err;
  BOOST_CHECK(config.loadFromString(TEST_CONFIGURATION_NULLLINES, &err));
}

const std::string TEST_CONFIGURATION_COMMENTS= \
"# Round Config\n" \
"#\n"\
"#{\n"\
"#  \"node\": {\n"\
"#    \"port\": 4649,\n"\
"#    \"ifaddr\": \"127.0.0.1\"\n"\
"#  }\n"\
"#  \"log\": {\n"\
"#    \"file\": \"/var/log/round.log\"\n"\
"#    \"level\": \"info\"\n"\
"#  }\n"\
"#}\n";

BOOST_AUTO_TEST_CASE(RoundConfigCommentTest) {
  Config config;
  Error err;
  BOOST_CHECK(config.loadFromString(TEST_CONFIGURATION_COMMENTS, &err));
}

const std::string TEST_CONFIGURATION_SAMPLE= \
"# Round Config\n" \
"\n"\
"{\n"\
"  \"node\": {\n"\
"    \"bind_port\": 4649,\n"\
"    \"bind_addr\": \"127.0.0.1\"\n"\
"  },\n"\
"  \"log\": {\n"\
"    \"file\": \"/var/log/round.log\",\n"\
"    \"level\": \"info\"\n"\
"  }\n"\
"}\n";

BOOST_AUTO_TEST_CASE(RoundConfigTest) {
  Config config;
  Error err;

  BOOST_CHECK(config.loadFromString(TEST_CONFIGURATION_SAMPLE, &err));

  std::string value;
  int ivalue;
  
  // Valid config
  
  BOOST_CHECK(config.getIntegerByPath("/node/bind_port", &ivalue, &err));
  BOOST_CHECK_EQUAL(4649, ivalue);

  BOOST_CHECK(config.getStringByPath("/node/bind_addr", &value, &err));
  BOOST_CHECK_EQUAL(value.compare("127.0.0.1"), 0);

  BOOST_CHECK(config.getStringByPath("/log/file", &value, &err));
  BOOST_CHECK_EQUAL(value.compare("/var/log/round.log"), 0);

  BOOST_CHECK(config.getStringByPath("/log/level", &value, &err));
  BOOST_CHECK_EQUAL(value.compare("info"), 0);

  // Invalid Config
  
  BOOST_CHECK(!config.getStringByPath("/loga/file", &value, &err));
  BOOST_CHECK(!config.getStringByPath("/log/files", &value, &err));
}

BOOST_AUTO_TEST_SUITE_END()
