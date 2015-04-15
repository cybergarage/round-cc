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

  time(&ts); ss << "key" << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setKey(val), true);
  BOOST_CHECK_EQUAL(reg.getKey(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  sval = reg.getKey();
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts); ss << "val" << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg.setValue(val), true);
  BOOST_CHECK_EQUAL(reg.getValue(&sval), true);
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  sval = reg.getValue();
  BOOST_CHECK_EQUAL(val.compare(sval), 0);
  
  time(&ts); ts += rand();
  BOOST_CHECK_EQUAL(reg.setTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);
  tval = reg.getTimestamp();
  BOOST_CHECK_EQUAL(tval, ts);

  time(&ts); ts += rand();
  BOOST_CHECK_EQUAL(reg.setLogicalTimestamp(ts), true);
  BOOST_CHECK_EQUAL(reg.getLogicalTimestamp(tval), true);
  BOOST_CHECK_EQUAL(tval, ts);
  tval = reg.getLogicalTimestamp();
  BOOST_CHECK_EQUAL(tval, ts);
}

BOOST_AUTO_TEST_CASE(RQLRregistryEqualsTest) {
  std::string val;
  time_t ts;
  std::stringstream ss;
  std::string sval;
  
  Registry reg01;
  
  time(&ts); ss << "key" << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg01.setKey(val), true);
  
  time(&ts); ss << "val" << ts; val = ss.str();
  BOOST_CHECK_EQUAL(reg01.setValue(val), true);

  time(&ts); ts += rand();
  BOOST_CHECK_EQUAL(reg01.setTimestamp(ts), true);
  
  time(&ts); ts += rand();
  BOOST_CHECK_EQUAL(reg01.setLogicalTimestamp(ts), true);

  Registry reg02;
  
  BOOST_CHECK_EQUAL(reg01.equals(reg02), false);
  BOOST_CHECK_EQUAL(reg01.equalsWithTimestamp(reg02), false);
  
  reg02 = reg01;
  BOOST_CHECK_EQUAL(reg01.equals(reg02), true);
  BOOST_CHECK_EQUAL(reg01.equalsWithTimestamp(reg02), true);
}

BOOST_AUTO_TEST_CASE(RQLRregistryMapBasicMethodTest) {
  RegistryMap regMap;
  BOOST_CHECK_EQUAL(regMap.size(), 0);
  
  for (int n=0; n<10; n++) {
    std::stringstream ss;
    time_t ts;
    
    Registry inReg;
    
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
    BOOST_CHECK_EQUAL(inReg.setKey(key), true);
    BOOST_CHECK_EQUAL(inReg.setValue(val), true);
    
    time(&ts); ts += rand();
    BOOST_CHECK_EQUAL(inReg.setTimestamp(ts), true);
    
    time(&ts); ts += rand();
    BOOST_CHECK_EQUAL(inReg.setLogicalTimestamp(ts), true);
    
    BOOST_CHECK_EQUAL(regMap.size(), n);
    BOOST_CHECK_EQUAL(regMap.set(inReg), true);
    BOOST_CHECK_EQUAL(regMap.size(), (n+1));
    
    Registry outReg;
    
    BOOST_CHECK_EQUAL(regMap.get(key, &outReg), true);
    BOOST_CHECK_EQUAL(inReg.equals(outReg), true);
    BOOST_CHECK_EQUAL(inReg.equalsWithTimestamp(outReg), true);
  }
}

BOOST_AUTO_TEST_CASE(RQLRregistryMapSimpleMethodTest) {
  RegistryMap regMap;
  BOOST_CHECK_EQUAL(regMap.size(), 0);
    
  for (int n=0; n<10; n++) {
      
    std::stringstream ss;
    time_t ts;
      
    time(&ts); ts += rand(); ss << ts;
    std::string key = "key" + ss.str();
    std::string val = "val" + ss.str();
      
    BOOST_CHECK_EQUAL(regMap.size(), n);
    BOOST_CHECK_EQUAL(regMap.get(key, &val), false);
      
    BOOST_CHECK_EQUAL(regMap.set(key, val), true);
    BOOST_CHECK_EQUAL(regMap.size(), (n+1));
      
    std::string outVal;
      
    BOOST_CHECK_EQUAL(regMap.get(key, &outVal), true);
    BOOST_CHECK_EQUAL(val.compare(outVal), 0);
  }
}
  
BOOST_AUTO_TEST_SUITE_END()
