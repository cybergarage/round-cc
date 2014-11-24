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

#include <round/core/Script.h>

using namespace std;
using namespace Round;

class TestScript : public Script {
  
public:
  TestScript() {
  }
  
  bool run(const std::string &params, std::string *results, Error *error) {return true;}
};

BOOST_AUTO_TEST_CASE(ScriptBasicTest) {
  TestScript script;

  BOOST_CHECK(!script.hasName());
  BOOST_CHECK_EQUAL(script.getName().length(), 0);
  BOOST_CHECK_EQUAL(script.getContent().length(), 0);
  
  const std::string TEST_SCRIPT_NAME = "test_script_name";
  BOOST_CHECK(script.setName(TEST_SCRIPT_NAME));
  BOOST_CHECK(script.hasName());
  BOOST_CHECK_EQUAL(TEST_SCRIPT_NAME.compare(script.getName()), 0);
  
  const std::string TEST_SCRIPT_CONTENT = "test_script_content";
  BOOST_CHECK(script.setContent(TEST_SCRIPT_CONTENT));
  BOOST_CHECK_EQUAL(TEST_SCRIPT_CONTENT.compare(script.getContent()), 0);
  
  BOOST_CHECK(script.run("", NULL, NULL));
}
