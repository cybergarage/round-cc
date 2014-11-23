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
  
  bool run() {return true;}
};

BOOST_AUTO_TEST_CASE(ScriptNodeTest) {
  TestScript script;
  BOOST_CHECK(script.run());
}
