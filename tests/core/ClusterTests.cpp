/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>

#include <boost/test/unit_test.hpp>
#include <round/core/Cluster.h>

const std::string TEST_CLUSTER_NAME = "testCluster";
const std::string TEST_CLUSTER_NAME_1 = "testCluster1";
const std::string TEST_CLUSTER_NAME_2 = "testCluster2";

BOOST_AUTO_TEST_CASE(ClusterNameTest) {
  Round::Cluster cluster(TEST_CLUSTER_NAME);

  BOOST_CHECK_EQUAL(TEST_CLUSTER_NAME, cluster.getName());
  BOOST_CHECK(cluster.isName(TEST_CLUSTER_NAME));

  BOOST_CHECK(!cluster.isName(TEST_CLUSTER_NAME_1));
  BOOST_CHECK(!cluster.isName(TEST_CLUSTER_NAME_2));
}

BOOST_AUTO_TEST_CASE(ClusterCopyTest) {
  Round::Cluster cluster1(TEST_CLUSTER_NAME_1);

  Round::Cluster cluster2(&cluster1);
  BOOST_CHECK(cluster1.equals(&cluster2));
}

BOOST_AUTO_TEST_CASE(ClusterEqualTest) {
  Round::Cluster cluster1(TEST_CLUSTER_NAME_1);
  BOOST_CHECK(cluster1.equals(&cluster1));

  Round::Cluster cluster2(TEST_CLUSTER_NAME_2);
  BOOST_CHECK(!cluster1.equals(&cluster2));
  BOOST_CHECK(!cluster2.equals(&cluster1));

  Round::Cluster cluster3(TEST_CLUSTER_NAME_1);
  BOOST_CHECK(cluster1.equals(&cluster3));
  BOOST_CHECK(cluster3.equals(&cluster1));
}
