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

#include <round/core/RQL.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(rql)

BOOST_AUTO_TEST_CASE(RQLRequestParserTest) {
  std::string rql;
  Error err;
  std::string method;
  std::string params;
  std::string dest;
  
  RQLRequest rqlReq;
  
  rql = "echo(?,hello)";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), true);
  BOOST_CHECK_EQUAL(rqlReq.getMethod(&method), true);
  BOOST_CHECK_EQUAL(method.compare("echo"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getDest(&dest), true);
  BOOST_CHECK_EQUAL(dest.compare("?"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getParams(&params), true);
  BOOST_CHECK_EQUAL(params.compare("hello"), 0);
  
  rql = "hello(?)";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), true);
  BOOST_CHECK_EQUAL(rqlReq.getMethod(&method), true);
  BOOST_CHECK_EQUAL(method.compare("hello"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getDest(&dest), true);
  BOOST_CHECK_EQUAL(dest.compare("?"), 0);
  BOOST_CHECK_EQUAL(rqlReq.hasParams(), false);
}

BOOST_AUTO_TEST_CASE(RQLRequestNoParamParserTest) {
  std::string rql;
  Error err;
  std::string method;
  std::string params;
  std::string dest;

  RQLRequest rqlReq;
  
  rql = "echo(?,hello)";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), true);
  BOOST_CHECK_EQUAL(rqlReq.getMethod(&method), true);
  BOOST_CHECK_EQUAL(method.compare("echo"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getDest(&dest), true);
  BOOST_CHECK_EQUAL(dest.compare("?"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getParams(&params), true);
  BOOST_CHECK_EQUAL(params.compare("hello"), 0);

  rql = "hello(?)";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), true);
  BOOST_CHECK_EQUAL(rqlReq.getMethod(&method), true);
  BOOST_CHECK_EQUAL(method.compare("hello"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getDest(&dest), true);
  BOOST_CHECK_EQUAL(dest.compare("?"), 0);
  BOOST_CHECK_EQUAL(rqlReq.hasParams(), false);
}

BOOST_AUTO_TEST_CASE(RQLInvalidRequestParserTest) {
  std::string rql;
  Error err;
  
  RQLRequest rqlReq;
  
  rql = "";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);

  rql = "echo";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);

  rql = "echo(";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);

  rql = "echo()";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);

  rql = "echo(*";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);

  rql = "echo(*, hello";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), false);
}

BOOST_AUTO_TEST_CASE(RQLRequestSetMethodTest) {
  std::string rql;
  Error err;
  std::string method;
  std::string params;
  std::string dest;
  
  RQLRequest rqlReq;
  
  rql = "set_method(0, { \"lang\":\"js\", \"code\":\"function echo(params) {return params;}\" })";
  BOOST_CHECK_EQUAL(rqlReq.parseQuery(rql, &err), true);
  BOOST_CHECK_EQUAL(rqlReq.getMethod(&method), true);
  BOOST_CHECK_EQUAL(method.compare("set_method"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getDest(&dest), true);
  BOOST_CHECK_EQUAL(dest.compare("0"), 0);
  BOOST_CHECK_EQUAL(rqlReq.getParams(&params), true);
  BOOST_CHECK_EQUAL(params.compare("{ \"lang\":\"js\", \"code\":\"function echo(params) {return params;}\" }"), 0);
}

BOOST_AUTO_TEST_SUITE_END()
