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

#include <round/core/NodeMessage.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(node)

BOOST_AUTO_TEST_CASE(NodeRequestConstructorTest) {
  const std::string TEST_METHOD = "hello";
  
  NodeRequest nodeReq(TEST_METHOD);
  BOOST_CHECK(nodeReq.hasMethod());
  BOOST_CHECK(nodeReq.isMethod(TEST_METHOD));

  BOOST_CHECK(!nodeReq.isMethod(""));
}

BOOST_AUTO_TEST_CASE(NodeRequestParserTest) {
  Error error;
  NodeRequestParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  NodeRequest *nodeReq = static_cast<NodeRequest *>(jsonParser.getRootObject());
  BOOST_CHECK(nodeReq);
}

BOOST_AUTO_TEST_CASE(NodeRequestOptionTest) {
  NodeRequest nodeReq;
  
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);

  BOOST_CHECK(nodeReq.setSync(false));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), true);

  BOOST_CHECK(nodeReq.setSync(true));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);

  BOOST_CHECK(nodeReq.setAsync(true));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), false);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), true);
  
  BOOST_CHECK(nodeReq.setAsync(false));
  BOOST_CHECK_EQUAL(nodeReq.isSync(), true);
  BOOST_CHECK_EQUAL(nodeReq.isAsync(), false);
}

BOOST_AUTO_TEST_CASE(NodeRequestCopyTest) {
  Error error;
  NodeRequestParser jsonParser;
  BOOST_CHECK(jsonParser.parse("{\"name\": \"John Smith\", \"age\": 33}", &error));
  BOOST_CHECK(jsonParser.getRootObject());
  BOOST_CHECK(jsonParser.getRootObject()->isDictionary());
  NodeRequest *nodeReq = static_cast<NodeRequest *>(jsonParser.getRootObject());
  BOOST_CHECK(nodeReq);

  NodeRequest copyNodeReq(nodeReq);
  BOOST_CHECK(copyNodeReq.equals(nodeReq));
}

BOOST_AUTO_TEST_CASE(NodeRequestSetWithDefaultsTest) {
  NodeRequest nodeReq;
  std::string reqParams;
  std::string defaults;
  std::string params;
  std::string param;
  
  // Request has no params (Use default params)

  BOOST_CHECK(nodeReq.clear());
  reqParams = "";
  defaults = "default";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(defaults), 0);
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "";
  defaults = "{\"name\": \"John Smith\", \"age\": 33}";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(defaults), 0);
  
  // Request or default is not JSON format. (Use request params)
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "hello";
  defaults = "{\"name\": \"John Smith\", \"age\": 33}";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(reqParams), 0);
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "{\"name\": \"John Smith\", \"age\": 33}";
  defaults = "default";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare(reqParams), 0);
  
  // Request and default are JSONDictionary (Merge params)
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "{\"name\": \"John Smith\"}";
  defaults = "{\"age\": 33}";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare("{\"age\":33,\"name\":\"John Smith\"}"), 0);
  
  // Request and default are JSONArray (Merge params)
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "[\"John Smith\"]";
  defaults = "[33]";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare("[\"John Smith\",33]"), 0);
  
  // Request and default are not same data type (Use request params)
  
  BOOST_CHECK(nodeReq.clear());
  reqParams = "{\"age\":33,\"name\":\"John Smith\"}";
  defaults = "[\"John Smith\",33]";
  BOOST_CHECK(nodeReq.setParamsWithDefault(reqParams, defaults));
  BOOST_CHECK(nodeReq.getParams(&params));
  BOOST_CHECK_EQUAL(params.compare("{\"age\":33,\"name\":\"John Smith\"}"), 0);
}

BOOST_AUTO_TEST_SUITE_END()

