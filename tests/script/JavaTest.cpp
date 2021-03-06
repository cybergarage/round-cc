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

#include <vector>
#include <round/script/Java.h>

#include "TestScript.h"

#if defined(ROUND_SUPPORT_JAVA_JNI)

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(script)

// Genarated JDK 1.7.0_51
static const std::string TEST_ECHO_BASE64_JDK170_CLASS = "echo170";
static const std::string TEST_ECHO_BASE64_JDK170_CODE = "yv66vgAAADMADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAApTb3VyY2VGaWxlAQAMZWNobzE3MC5qYXZhDAAEAAUBAAdlY2hvMTcwAQAQamF2YS9sYW5nL09iamVjdAAhAAIAAwAAAAAAAgABAAQABQABAAYAAAAhAAEAAQAAAAUqtwABsQAAAAEABwAAAAoAAgAAAAIABAADAAEACAAJAAEABgAAABoAAQACAAAAAiuwAAAAAQAHAAAABgABAAAABQABAAoAAAACAAs=";

// Genarated by JDK 1.6.0_65
static const std::string TEST_ECHO_BASE64_JDK160_CLASS = "echo160";
static const std::string TEST_ECHO_BASE64_JDK160_CODE = "yv66vgAAADIADwoAAwAMBwANBwAOAQAGPGluaXQ+AQADKClWAQAEQ29kZQEAD0xpbmVOdW1iZXJUYWJsZQEADnByb2Nlc3NNZXNzYWdlAQAmKExqYXZhL2xhbmcvU3RyaW5nOylMamF2YS9sYW5nL1N0cmluZzsBAApTb3VyY2VGaWxlAQAMZWNobzE2MC5qYXZhDAAEAAUBAAdlY2hvMTYwAQAQamF2YS9sYW5nL09iamVjdAAhAAIAAwAAAAAAAgABAAQABQABAAYAAAAhAAEAAQAAAAUqtwABsQAAAAEABwAAAAoAAgAAAAIABAADAAEACAAJAAEABgAAABoAAQACAAAAAiuwAAAAAQAHAAAABgABAAAABQABAAoAAAACAAs=";

BOOST_AUTO_TEST_CASE(JavaEngineClassLoaderBase64Test) {

  std::vector<std::string> classNames;
  std::vector<byte *> classCodes;
  std::vector<size_t> classCodeLengths;
  std::vector<int> classCodeEncords;
  
#if !defined(__APPLE__)
  // TODO Generated byte codes using JDK 1.7 are not run on MacOSX
  classNames.push_back(TEST_ECHO_BASE64_JDK170_CLASS);
  classCodes.push_back((byte *)TEST_ECHO_BASE64_JDK170_CODE.c_str());
  classCodeLengths.push_back(TEST_ECHO_BASE64_JDK170_CODE.length());
  classCodeEncords.push_back(Script::ENCODING_BASE64);
#endif
  
  // TODO Generated byte codes using JDK 1.6 are OK on MacOSX, but can not redefine class.
  classNames.push_back(TEST_ECHO_BASE64_JDK160_CLASS);
  classCodes.push_back((byte *)TEST_ECHO_BASE64_JDK160_CODE.c_str());
  classCodeLengths.push_back(TEST_ECHO_BASE64_JDK160_CODE.length());
  classCodeEncords.push_back(Script::ENCODING_BASE64);

  JavaEngine javaEngine;
  size_t nTestCodeCnt = classNames.size();
  for (size_t n=0; n<nTestCodeCnt; n++) {
    Script *testScript = new Script(JavaEngine::LANGUAGE, classNames.at(n), classCodes.at(n), classCodeLengths.at(n));
    BOOST_CHECK(!testScript->isBinaryCode());
    BOOST_CHECK(!testScript->hasEncording());
    testScript->setEncording(classCodeEncords.at(n));
    BOOST_CHECK(testScript->hasEncording());
    BOOST_CHECK(javaEngine.compile(testScript));
    delete testScript;
  }
}

BOOST_AUTO_TEST_CASE(JavaEngineEchoTest) {
  Error err;
  ScriptManager scriptMgr;

  BOOST_CHECK(scriptMgr.setEngine(new JavaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_ECHO_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_ECHO_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_ECHO_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runEchoMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(JavaEngineSumTest) {
  Error err;
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_SUM_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_SUM_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SUM_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runSumMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_CASE(JavaEngineCounterTest) {
  Error err;
  ScriptManager scriptMgr;
  
  BOOST_CHECK(scriptMgr.setEngine(new JavaEngine()));
  BOOST_CHECK(scriptMgr.hasEngine(JavaEngine::LANGUAGE));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_COUNTER_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_COUNTER_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_COUNTER_NAME));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_SETCOUNTER_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_SETCOUNTER_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_SETCOUNTER_NAME));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_GETCOUNTER_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_GETCOUNTER_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_GETCOUNTER_NAME));
  
  BOOST_CHECK(scriptMgr.setScript(Test::SCRIPT_INCCOUNTER_NAME, JavaEngine::LANGUAGE, Round::Test::JAVA_INCCOUNTER_CODE, Script::ENCODING_BASE64, &err));
  BOOST_CHECK(scriptMgr.hasScript(Test::SCRIPT_INCCOUNTER_NAME));
  
  Test::ScriptTestController scriptTestController;
  scriptTestController.runCounterMethodTest(&scriptMgr);
}

BOOST_AUTO_TEST_SUITE_END()

#endif

