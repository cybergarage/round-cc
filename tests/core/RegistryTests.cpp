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

#include <sstream>
#include <round/core/Registry.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(registry)

BOOST_AUTO_TEST_CASE(RQLRregistryBasicMethodTest) {
  std::string val;
  time_t ts;
  std::stringstream ss;
  std::string sval;
  time_t tval;
  
  Registry reg;
  
  BOOST_CHECK_EQUAL(reg.getKey(&sval), false);
  BOOST_CHECK_EQUAL(reg.getValue(&sval), false);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), false);
  BOOST_CHECK_EQUAL(reg.getLogicalTimestamp(tval), false);

  time(&ts); ss << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setKey(val), true);
  BOOST_CHECK_EQUAL(reg.getKey(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts); ss << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setValue(val), true);
  BOOST_CHECK_EQUAL(reg.getValue(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts);
  BOOST_CHECK_EQUAL(reg.setTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);

  time(&ts);
  BOOST_CHECK_EQUAL(reg.setLogicalTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getLogicalTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);
}

BOOST_AUTO_TEST_CASE(RQLRregistryMapMethodTest) {
  RegistryMap regMap;
  BOOST_CHECK_EQUAL(regMap.size(), 0);
  
  for (int n=0; n<10; n++) {
  
    std::stringstream ss;
    time_t ts;
    time(&ts); ss << ts;
    
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    
    Registry inReg;
    BOOST_CHECK_EQUAL(inReg.setKey(key), true);
    BOOST_CHECK_EQUAL(inReg.setValue(val), true);
    BOOST_CHECK_EQUAL(inReg.setTimestamp(ts), true);
    BOOST_CHECK_EQUAL(inReg.setLogicalTimestamp(ts), true);
    
    BOOST_CHECK_EQUAL(regMap.size(), n);
    BOOST_CHECK_EQUAL(regMap.set(inReg), true);
    BOOST_CHECK_EQUAL(regMap.size(), (n+1));
    
    Registry outReg;
    BOOST_CHECK_EQUAL(inReg.equals(inReg), true);
    BOOST_CHECK_EQUAL(inReg.equalsWithTimestamp(inReg), true);
  }
}
  
BOOST_AUTO_TEST_SUITE_END()
