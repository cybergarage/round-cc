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

#include <round/core/Route.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(route)

BOOST_AUTO_TEST_CASE(RouteTest) {
  const std::string TEST_NAME = "rname";
  const std::string TEST_SRC_METHOD = "smethod";
  const std::string TEST_SRC_NODE = "snode";
  const std::string TEST_SRC_CLUSTER = "scluster";
  
  const std::string TEST_DEST_METHOD = "dmethod";
  const std::string TEST_DEST_NODE = "dnode";
  const std::string TEST_DEST_CLUSTER = "dcluster";
  
  Route route;
  std::string name, object;
  
  // initialize node
  
  BOOST_CHECK_EQUAL(route.isValid(), false);
  BOOST_CHECK_EQUAL(route.getName(&name), false);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), false);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), false);
  BOOST_CHECK_EQUAL(route.getSourceMethod(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationMethod(&object), false);

  // "name"

  BOOST_CHECK_EQUAL(route.setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(route.isValid(), false);
  BOOST_CHECK_EQUAL(route.getName(&name), true);
  BOOST_CHECK_EQUAL(name.compare(TEST_NAME), 0);
  
  // "method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), false);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::NODE_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);

  // "method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::NODE_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // "node.method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_NODE + "." + TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  // "node.method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_NODE + "." + TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // "cluster.node.method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_CLUSTER + "." + TEST_SRC_NODE + "." + TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  // "cluster.node.method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_CLUSTER + "." + TEST_DEST_NODE + "." + TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // Last Check
  
  BOOST_CHECK_EQUAL(route.isValid(), true);
  
  BOOST_CHECK_EQUAL(route.getName(&name), true);
  BOOST_CHECK_EQUAL(name.compare(TEST_NAME), 0);
  
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationMethod(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);
}

BOOST_AUTO_TEST_SUITE_END()

