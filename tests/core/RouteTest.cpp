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

#include <round/core/Route.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(route)

BOOST_AUTO_TEST_CASE(RouteObjectsParseTest) {
  const std::string TEST_METHOD = "method";
  const std::string TEST_NODE = "node";
  const std::string TEST_CLUSTER = "cluster";
  
  RouteObjects routeObjs;
  std::string name, object, path;
  
  // Initialize node
  
  BOOST_CHECK_EQUAL(routeObjs.isValid(), false);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), false);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), false);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), false);
  
  // Parse null object
  
  BOOST_CHECK_EQUAL(routeObjs.parse(""), false);
  BOOST_CHECK_EQUAL(routeObjs.isValid(), false);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), false);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), false);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), false);
  
  // "method" (Src)
  
  BOOST_CHECK_EQUAL(routeObjs.parse(TEST_METHOD), true);
  BOOST_CHECK_EQUAL(routeObjs.isValid(), true);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::NODE_DEFALUT), 0);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_METHOD), 0);
  BOOST_CHECK_EQUAL(routeObjs.toString(&path), true);
  BOOST_CHECK_EQUAL(path.compare(TEST_METHOD), 0);
  
  // "node.method" (Src)
  
  BOOST_CHECK_EQUAL(routeObjs.parse(TEST_NODE + "." + TEST_METHOD), true);
  BOOST_CHECK_EQUAL(routeObjs.isValid(), true);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_NODE), 0);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_METHOD), 0);
  BOOST_CHECK_EQUAL(routeObjs.toString(&path), true);
  BOOST_CHECK_EQUAL(path.compare(TEST_NODE + "." + TEST_METHOD), 0);
  
  // "cluster.node.method" (Src)
  
  BOOST_CHECK_EQUAL(routeObjs.parse(TEST_CLUSTER + "." + TEST_NODE + "." + TEST_METHOD), true);
  BOOST_CHECK_EQUAL(routeObjs.isValid(), true);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_NODE), 0);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_METHOD), 0);
  BOOST_CHECK_EQUAL(routeObjs.toString(&path), true);
  BOOST_CHECK_EQUAL(path.compare(TEST_CLUSTER + "." + TEST_NODE + "." + TEST_METHOD), 0);
}

BOOST_AUTO_TEST_CASE(RouteObjectsConstructorTest) {
  const std::string TEST_METHOD = "method";
  const std::string TEST_NODE = "node";
  const std::string TEST_CLUSTER = "cluster";
  
  // "cluster.node.method"
  
  RouteObjects routeObjs(TEST_CLUSTER + "." + TEST_NODE + "." + TEST_METHOD);
  std::string name, object;
  
  BOOST_CHECK_EQUAL(routeObjs.isValid(), true);
  BOOST_CHECK_EQUAL(routeObjs.getCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(routeObjs.getNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_NODE), 0);
  BOOST_CHECK_EQUAL(routeObjs.getTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_METHOD), 0);
}

BOOST_AUTO_TEST_CASE(RouteObjectsEqualsTest) {
  const std::string TEST_01_METHOD = "method01";
  const std::string TEST_01_NODE = "node01";
  const std::string TEST_01_CLUSTER = "cluster01";
  const std::string TEST_01_OBJ = TEST_01_CLUSTER + "." + TEST_01_NODE + "." + TEST_01_METHOD;

  const std::string TEST_02_METHOD = "method02";
  const std::string TEST_02_NODE = "node02";
  const std::string TEST_02_CLUSTER = "cluster02";
  const std::string TEST_02_OBJ = TEST_02_CLUSTER + "." + TEST_02_NODE + "." + TEST_02_METHOD;

  RouteObjects routeObjs(TEST_01_OBJ);
  BOOST_CHECK_EQUAL(routeObjs.equals(routeObjs), true);
  BOOST_CHECK_EQUAL(routeObjs.equals(TEST_01_OBJ), true);

  RouteObjects routeObjs01(TEST_01_OBJ);
  BOOST_CHECK_EQUAL(routeObjs01.equals(TEST_01_OBJ), true);
  BOOST_CHECK_EQUAL(routeObjs.equals(TEST_01_OBJ), true);
  
  RouteObjects routeObjs02(TEST_02_OBJ);
  BOOST_CHECK_EQUAL(routeObjs02.equals(routeObjs02), true);
  BOOST_CHECK_EQUAL(routeObjs02.equals(TEST_02_OBJ), true);

  BOOST_CHECK_EQUAL(routeObjs.equals(routeObjs01), true);
  BOOST_CHECK_EQUAL(routeObjs.equals(TEST_01_OBJ), true);
  BOOST_CHECK_EQUAL(routeObjs.equals(routeObjs02), false);
  BOOST_CHECK_EQUAL(routeObjs.equals(TEST_02_OBJ), false);
}

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
  BOOST_CHECK_EQUAL(route.getSourceTarget(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), false);
  BOOST_CHECK_EQUAL(route.getDestinationTarget(&object), false);

  // "name"

  BOOST_CHECK_EQUAL(route.setName(TEST_NAME), true);
  BOOST_CHECK_EQUAL(route.isValid(), false);
  BOOST_CHECK_EQUAL(route.getName(&name), true);
  BOOST_CHECK_EQUAL(name.compare(TEST_NAME), 0);
  BOOST_CHECK_EQUAL(route.hasName(), true);
  
  // "method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), false);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::NODE_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);

  // "method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::NODE_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // "node.method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_NODE + "." + TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  // "node.method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_NODE + "." + TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(Route::CLUSTER_DEFALUT), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // "cluster.node.method" (Src)
  
  BOOST_CHECK_EQUAL(route.setSource(TEST_SRC_CLUSTER + "." + TEST_SRC_NODE + "." + TEST_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  // "cluster.node.method" (Dest)
  
  BOOST_CHECK_EQUAL(route.setDestination(TEST_DEST_CLUSTER + "." + TEST_DEST_NODE + "." + TEST_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.isValid(), true);
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  // type
  
  BOOST_CHECK_EQUAL(route.isValidType(), true);
  BOOST_CHECK_EQUAL(route.isPipe(), false);
  BOOST_CHECK_EQUAL(route.isEvent(), false);
  
  BOOST_CHECK_EQUAL(route.setType("balidtype"), true);
  BOOST_CHECK_EQUAL(route.isValidType(), false);
  BOOST_CHECK_EQUAL(route.isPipe(), false);
  BOOST_CHECK_EQUAL(route.isEvent(), false);
  
  BOOST_CHECK_EQUAL(route.setType(Route::TYPE_EVENT), true);
  BOOST_CHECK_EQUAL(route.isValidType(), true);
  BOOST_CHECK_EQUAL(route.isPipe(), false);
  BOOST_CHECK_EQUAL(route.isEvent(), true);
  
  BOOST_CHECK_EQUAL(route.setType(Route::TYPE_PIPE), true);
  BOOST_CHECK_EQUAL(route.isValidType(), true);
  BOOST_CHECK_EQUAL(route.isPipe(), true);
  BOOST_CHECK_EQUAL(route.isEvent(), false);
  
  // Last Check
  
  BOOST_CHECK_EQUAL(route.isValid(), true);
  
  BOOST_CHECK_EQUAL(route.getName(&name), true);
  BOOST_CHECK_EQUAL(name.compare(TEST_NAME), 0);
  
  BOOST_CHECK_EQUAL(route.getSourceCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getSourceNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_NODE), 0);
  BOOST_CHECK_EQUAL(route.getSourceTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_SRC_METHOD), 0);
  
  BOOST_CHECK_EQUAL(route.getDestinationCluster(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_CLUSTER), 0);
  BOOST_CHECK_EQUAL(route.getDestinationNode(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_NODE), 0);
  BOOST_CHECK_EQUAL(route.getDestinationTarget(&object), true);
  BOOST_CHECK_EQUAL(object.compare(TEST_DEST_METHOD), 0);

  BOOST_CHECK_EQUAL(route.isPipe(), true);
  BOOST_CHECK_EQUAL(route.isEvent(), false);
}

BOOST_AUTO_TEST_CASE(RouteEqualsTest) {
  const std::string TEST_01_NAME = "sname01";
  const std::string TEST_01_SRC_METHOD = "smethod01";
  const std::string TEST_01_SRC_NODE = "snode01";
  const std::string TEST_01_SRC_CLUSTER = "scluster01";
  const std::string TEST_01_DEST_METHOD = "dmethod01";
  const std::string TEST_01_DEST_NODE = "dnode01";
  const std::string TEST_01_DEST_CLUSTER = "dcluster01";
  
  const std::string TEST_02_NAME = "sname02";
  const std::string TEST_02_SRC_METHOD = "smethod02";
  const std::string TEST_02_SRC_NODE = "snode02";
  const std::string TEST_02_SRC_CLUSTER = "scluster02";
  const std::string TEST_02_DEST_METHOD = "dmethod02";
  const std::string TEST_02_DEST_NODE = "dnode02";
  const std::string TEST_02_DEST_CLUSTER = "dcluster02";
  
  Route route;
  BOOST_CHECK_EQUAL(route.setName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(route.setSource(TEST_01_SRC_CLUSTER + "." + TEST_01_SRC_NODE + "." + TEST_01_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route.setDestination(TEST_01_DEST_CLUSTER + "." + TEST_01_DEST_NODE + "." + TEST_01_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route.equals(&route), true);

  Route route01;
  BOOST_CHECK_EQUAL(route01.setName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(route01.setSource(TEST_01_SRC_CLUSTER + "." + TEST_01_SRC_NODE + "." + TEST_01_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route01.setDestination(TEST_01_DEST_CLUSTER + "." + TEST_01_DEST_NODE + "." + TEST_01_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route01.equals(&route01), true);

  Route route02;
  BOOST_CHECK_EQUAL(route02.setName(TEST_02_NAME), true);
  BOOST_CHECK_EQUAL(route02.setSource(TEST_02_SRC_CLUSTER + "." + TEST_02_SRC_NODE + "." + TEST_02_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route02.setDestination(TEST_02_DEST_CLUSTER + "." + TEST_02_DEST_NODE + "." + TEST_02_DEST_METHOD), true);
  BOOST_CHECK_EQUAL(route02.equals(&route02), true);
  
  BOOST_CHECK_EQUAL(route.equals(&route01), true);
  BOOST_CHECK_EQUAL(route.equals(&route02), false);
}

BOOST_AUTO_TEST_CASE(RouteListTest) {
  const std::string TEST_01_NAME = "sname01";
  const std::string TEST_01_SRC_METHOD = "smethod01";
  const std::string TEST_01_SRC_NODE = "snode01";
  const std::string TEST_01_SRC_CLUSTER = "scluster01";
  const std::string TEST_01_SRC_OBJ = TEST_01_SRC_CLUSTER + "." + TEST_01_SRC_NODE + "." + TEST_01_SRC_METHOD;
  const std::string TEST_01_DEST_METHOD = "dmethod01";
  const std::string TEST_01_DEST_NODE = "dnode01";
  const std::string TEST_01_DEST_CLUSTER = "dcluster01";
  const std::string TEST_01_DEST_OBJ = TEST_01_DEST_CLUSTER + "." + TEST_01_DEST_NODE + "." + TEST_01_DEST_METHOD;
  
  const std::string TEST_02_NAME = "sname02";
  const std::string TEST_02_SRC_METHOD = "smethod02";
  const std::string TEST_02_SRC_NODE = "snode02";
  const std::string TEST_02_SRC_CLUSTER = "scluster02";
  const std::string TEST_02_SRC_OBJ = TEST_02_SRC_CLUSTER + "." + TEST_02_SRC_NODE + "." + TEST_02_SRC_METHOD;
  const std::string TEST_02_DEST_METHOD = "dmethod02";
  const std::string TEST_02_DEST_NODE = "dnode02";
  const std::string TEST_02_DEST_CLUSTER = "dcluster02";
  const std::string TEST_02_DEST_OBJ = TEST_02_DEST_CLUSTER + "." + TEST_02_DEST_NODE + "." + TEST_02_DEST_METHOD;
  
  RouteList routeList;
  Route *route;
  
  BOOST_CHECK_EQUAL(routeList.size(), 0);

  // addRoute
  
  BOOST_CHECK_EQUAL(routeList.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  route = routeList.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  route = routeList.findRouteBySouceObject(TEST_01_SRC_OBJ);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(route->isSource(TEST_01_SRC_OBJ), true);
  BOOST_CHECK_EQUAL(route->isSourceMethod(TEST_01_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route->isDestination(TEST_01_DEST_OBJ), true);

  BOOST_CHECK_EQUAL(routeList.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), false);
  
  BOOST_CHECK_EQUAL(routeList.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), true);
  route = routeList.findRouteByName(TEST_02_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  route = routeList.findRouteBySouceObject(TEST_02_SRC_OBJ);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  BOOST_CHECK_EQUAL(route->isSource(TEST_02_SRC_OBJ), true);
  BOOST_CHECK_EQUAL(route->isSourceMethod(TEST_02_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route->isDestination(TEST_02_DEST_OBJ), true);

  BOOST_CHECK_EQUAL(routeList.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), false);

  // setRoute

  const std::string TEST_01P_SRC_METHOD = "smethod01+";
  const std::string TEST_01P_SRC_NODE = "snode01+";
  const std::string TEST_01P_SRC_CLUSTER = "scluster01+";
  const std::string TEST_01P_SRC_OBJ = TEST_01P_SRC_CLUSTER + "." + TEST_01P_SRC_NODE + "." + TEST_01P_SRC_METHOD;
  const std::string TEST_01P_DEST_METHOD = "dmethod01+";
  const std::string TEST_01P_DEST_NODE = "dnode01+";
  const std::string TEST_01P_DEST_CLUSTER = "dcluster01+";
  const std::string TEST_01P_DEST_OBJ = TEST_01P_DEST_CLUSTER + "." + TEST_01P_DEST_NODE + "." + TEST_01P_DEST_METHOD;
  
  BOOST_CHECK_EQUAL(routeList.setRoute(TEST_01_NAME, TEST_01P_SRC_OBJ, TEST_01P_DEST_OBJ), true);
  route = routeList.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  route = routeList.findRouteBySouceObject(TEST_01P_SRC_OBJ);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(route->isSource(TEST_01P_SRC_OBJ), true);
  BOOST_CHECK_EQUAL(route->isSourceMethod(TEST_01P_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route->isDestination(TEST_01P_DEST_OBJ), true);
  
  BOOST_CHECK_EQUAL(routeList.setRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  route = routeList.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  route = routeList.findRouteBySouceObject(TEST_01_SRC_OBJ);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(route->isSource(TEST_01_SRC_OBJ), true);
  BOOST_CHECK_EQUAL(route->isSourceMethod(TEST_01_SRC_METHOD), true);
  BOOST_CHECK_EQUAL(route->isDestination(TEST_01_DEST_OBJ), true);
}

BOOST_AUTO_TEST_CASE(RouteMapByNameTest) {
  const std::string TEST_01_NAME = "sname01";
  const std::string TEST_01_SRC_METHOD = "smethod01";
  const std::string TEST_01_SRC_NODE = "snode01";
  const std::string TEST_01_SRC_CLUSTER = "scluster01";
  const std::string TEST_01_SRC_OBJ = TEST_01_SRC_CLUSTER + "." + TEST_01_SRC_NODE + "." + TEST_01_SRC_METHOD;
  const std::string TEST_01_DEST_METHOD = "dmethod01";
  const std::string TEST_01_DEST_NODE = "dnode01";
  const std::string TEST_01_DEST_CLUSTER = "dcluster01";
  const std::string TEST_01_DEST_OBJ = TEST_01_DEST_CLUSTER + "." + TEST_01_DEST_NODE + "." + TEST_01_DEST_METHOD;
  
  const std::string TEST_02_NAME = "sname02";
  const std::string TEST_02_SRC_METHOD = "smethod02";
  const std::string TEST_02_SRC_NODE = "snode02";
  const std::string TEST_02_SRC_CLUSTER = "scluster02";
  const std::string TEST_02_SRC_OBJ = TEST_02_SRC_CLUSTER + "." + TEST_02_SRC_NODE + "." + TEST_02_SRC_METHOD;
  const std::string TEST_02_DEST_METHOD = "dmethod02";
  const std::string TEST_02_DEST_NODE = "dnode02";
  const std::string TEST_02_DEST_CLUSTER = "dcluster02";
  const std::string TEST_02_DEST_OBJ = TEST_02_DEST_CLUSTER + "." + TEST_02_DEST_NODE + "." + TEST_02_DEST_METHOD;
  
  RouteMap routeMap;
  Route *route;

  BOOST_CHECK_EQUAL(routeMap.size(), 0);
  BOOST_CHECK_EQUAL(routeMap.count(), 0);

  // addRoute
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);
  
  route = routeMap.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);

  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), false);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);

  route = routeMap.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);

  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findRouteByName(TEST_02_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), false);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findRouteByName(TEST_02_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  // setRoute
  
  BOOST_CHECK_EQUAL(routeMap.setRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findRouteByName(TEST_01_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);

  BOOST_CHECK_EQUAL(routeMap.setRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findRouteByName(TEST_02_NAME);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  // removeRoute
  
  BOOST_CHECK_EQUAL(routeMap.removeRouteByName(TEST_01_NAME), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);

  BOOST_CHECK_EQUAL(routeMap.removeRouteByName(TEST_02_NAME), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 0);
  BOOST_CHECK_EQUAL(routeMap.count(), 0);
}

BOOST_AUTO_TEST_CASE(RouteMapByRouteTest) {
  const std::string TEST_01_NAME = "sname01";
  const std::string TEST_01_SRC_METHOD = "smethod01";
  const std::string TEST_01_SRC_NODE = "snode01";
  const std::string TEST_01_SRC_CLUSTER = "scluster01";
  const std::string TEST_01_SRC_OBJ = TEST_01_SRC_CLUSTER + "." + TEST_01_SRC_NODE + "." + TEST_01_SRC_METHOD;
  const std::string TEST_01_DEST_METHOD = "dmethod01";
  const std::string TEST_01_DEST_NODE = "dnode01";
  const std::string TEST_01_DEST_CLUSTER = "dcluster01";
  const std::string TEST_01_DEST_OBJ = TEST_01_DEST_CLUSTER + "." + TEST_01_DEST_NODE + "." + TEST_01_DEST_METHOD;
  
  const std::string TEST_02_NAME = "sname02";
  const std::string TEST_02_SRC_METHOD = "smethod02";
  const std::string TEST_02_SRC_NODE = "snode02";
  const std::string TEST_02_SRC_CLUSTER = "scluster02";
  const std::string TEST_02_SRC_OBJ = TEST_02_SRC_CLUSTER + "." + TEST_02_SRC_NODE + "." + TEST_02_SRC_METHOD;
  const std::string TEST_02_DEST_METHOD = "dmethod02";
  const std::string TEST_02_DEST_NODE = "dnode02";
  const std::string TEST_02_DEST_CLUSTER = "dcluster02";
  const std::string TEST_02_DEST_OBJ = TEST_02_DEST_CLUSTER + "." + TEST_02_DEST_NODE + "." + TEST_02_DEST_METHOD;

  RouteMap routeMap;
  Route *route;

  Route route01(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ);
  Route route02(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ);
  
  BOOST_CHECK_EQUAL(routeMap.size(), 0);
  BOOST_CHECK_EQUAL(routeMap.count(), 0);
  
  // addRoute
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);
  
  route = routeMap.findSameRoute(&route01);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), false);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);
  
  route = routeMap.findSameRoute(&route01);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findSameRoute(&route02);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  BOOST_CHECK_EQUAL(routeMap.addRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), false);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findSameRoute(&route02);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  // setRoute
  
  BOOST_CHECK_EQUAL(routeMap.setRoute(TEST_01_NAME, TEST_01_SRC_OBJ, TEST_01_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findSameRoute(&route01);
  BOOST_CHECK_EQUAL(route->isName(TEST_01_NAME), true);
  
  BOOST_CHECK_EQUAL(routeMap.setRoute(TEST_02_NAME, TEST_02_SRC_OBJ, TEST_02_DEST_OBJ), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 2);
  BOOST_CHECK_EQUAL(routeMap.count(), 2);
  
  route = routeMap.findSameRoute(&route02);
  BOOST_CHECK_EQUAL(route->isName(TEST_02_NAME), true);
  
  // removeRoute
  
  BOOST_CHECK_EQUAL(routeMap.removeSameRoute(&route01), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 1);
  BOOST_CHECK_EQUAL(routeMap.count(), 1);

  BOOST_CHECK_EQUAL(routeMap.removeSameRoute(&route02), true);
  BOOST_CHECK_EQUAL(routeMap.size(), 0);
  BOOST_CHECK_EQUAL(routeMap.count(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
