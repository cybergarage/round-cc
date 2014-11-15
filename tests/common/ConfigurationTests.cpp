/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <string>
#include <round/common/Configuration.h>

using namespace std;
using namespace Round;

const std::string FRACTAL_CONFIGURATION_NULLLINES= \
"\n" \
"\n" \
"\n" \
"\n" \
"\n" \
"\n";

BOOST_AUTO_TEST_CASE(RoundConfigurationNullTest) {
Configuration config;

  BOOST_CHECK(config.loadFromString(FRACTAL_CONFIGURATION_NULLLINES));
  BOOST_CHECK_EQUAL(config.size(), 0);
}

const std::string FRACTAL_CONFIGURATION_COMMENTS= \
";\n" \
"; \n" \
"; Sample\n" \
";[sample]\n" \
";key = value\n" \
";\n";

BOOST_AUTO_TEST_CASE(RoundConfigurationCommentTest) {
Configuration config;

  BOOST_CHECK(config.loadFromString(FRACTAL_CONFIGURATION_COMMENTS));
  BOOST_CHECK_EQUAL(config.size(), 0);
}

const std::string FRACTAL_CONFIGURATION_SAMPLE01= \
"; Round Configuration\n" \
"; \n" \
"[node]\n" \
"name = round\n" \
"\n" \
"[httpd]\n" \
"port = 4649\n" \
"bind_address = 127.0.0.1\n" \
"\n" \
"[log]\n" \
"file = /var/log/round.log\n" \
"level = info\n" \
"\n";

BOOST_AUTO_TEST_CASE(RoundConfigurationSample01Test) {
Configuration config;

  BOOST_CHECK(config.loadFromString(FRACTAL_CONFIGURATION_SAMPLE01));
  BOOST_CHECK_EQUAL(config.size(), 3);

  std::string value;

  BOOST_CHECK(config.getString("node", "name", &value));
  BOOST_CHECK_EQUAL(value.compare("round"), 0);
  BOOST_CHECK(config.getStringByPath("/node/name", &value));
  BOOST_CHECK_EQUAL(value.compare("round"), 0);

  BOOST_CHECK(config.getString("httpd", "port", &value));
  BOOST_CHECK_EQUAL(value.compare("4649"), 0);
  BOOST_CHECK(config.getStringByPath("/httpd/port", &value));
  BOOST_CHECK_EQUAL(value.compare("4649"), 0);

  BOOST_CHECK(config.getString("httpd", "bind_address", &value));
  BOOST_CHECK_EQUAL(value.compare("127.0.0.1"), 0);
  BOOST_CHECK(config.getStringByPath("/httpd/bind_address", &value));
  BOOST_CHECK_EQUAL(value.compare("127.0.0.1"), 0);

  BOOST_CHECK(config.getString("log", "file", &value));
  BOOST_CHECK_EQUAL(value.compare("/var/log/round.log"), 0);
  BOOST_CHECK(config.getStringByPath("/log/file", &value));
  BOOST_CHECK_EQUAL(value.compare("/var/log/round.log"), 0);

  BOOST_CHECK(config.getString("log", "level", &value));
  BOOST_CHECK_EQUAL(value.compare("info"), 0);
  BOOST_CHECK(config.getStringByPath("/log/level", &value));
  BOOST_CHECK_EQUAL(value.compare("info"), 0);

  BOOST_CHECK(!config.getString("loga", "file", &value));
  BOOST_CHECK(!config.getString("log", "files", &value));
  BOOST_CHECK(!config.getStringByPath("/loga/file", &value));
  BOOST_CHECK(!config.getStringByPath("/log/files", &value));

  config.clear();
  BOOST_CHECK_EQUAL(config.size(), 0);
}

BOOST_AUTO_TEST_CASE(RoundConfigurationCopyTest) {
Configuration config;

  BOOST_CHECK(config.loadFromString(FRACTAL_CONFIGURATION_SAMPLE01));
  BOOST_CHECK_EQUAL(config.size(), 3);

  Configuration copyConfig;
  copyConfig = config;

  std::string value;

  BOOST_CHECK(copyConfig.getString("node", "name", &value));
  BOOST_CHECK_EQUAL(value.compare("round"), 0);
  BOOST_CHECK(copyConfig.getStringByPath("/node/name", &value));
  BOOST_CHECK_EQUAL(value.compare("round"), 0);

  BOOST_CHECK(copyConfig.getString("httpd", "port", &value));
  BOOST_CHECK_EQUAL(value.compare("4649"), 0);
  BOOST_CHECK(copyConfig.getStringByPath("/httpd/port", &value));
  BOOST_CHECK_EQUAL(value.compare("4649"), 0);

  BOOST_CHECK(copyConfig.getString("httpd", "bind_address", &value));
  BOOST_CHECK_EQUAL(value.compare("127.0.0.1"), 0);
  BOOST_CHECK(copyConfig.getStringByPath("/httpd/bind_address", &value));
  BOOST_CHECK_EQUAL(value.compare("127.0.0.1"), 0);

  BOOST_CHECK(copyConfig.getString("log", "file", &value));
  BOOST_CHECK_EQUAL(value.compare("/var/log/round.log"), 0);
  BOOST_CHECK(copyConfig.getStringByPath("/log/file", &value));
  BOOST_CHECK_EQUAL(value.compare("/var/log/round.log"), 0);

  BOOST_CHECK(copyConfig.getString("log", "level", &value));
  BOOST_CHECK_EQUAL(value.compare("info"), 0);
  BOOST_CHECK(copyConfig.getStringByPath("/log/level", &value));
  BOOST_CHECK_EQUAL(value.compare("info"), 0);
}

