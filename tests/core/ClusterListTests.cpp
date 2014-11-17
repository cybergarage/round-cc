/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <round/core/Cluster.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(RoundClusterAddTest) {
  const size_t clusterCount = 10;

  Cluster *clusters[clusterCount];
  ClusterList clusterList;

  for (size_t n = 0; n < clusterCount; n++) {
    clusters[n] = new Cluster();
    std::stringstream clusterName;
    clusterName << "cluster" << n;
    clusters[n]->setName(clusterName.str());
  }

  BOOST_CHECK(!clusterList.getFirstCluster());
  
  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(!clusterList.getCluster(clusters[n]->getName()));
    BOOST_CHECK(!clusterList.hasCluster(clusters[n]->getName()));
    BOOST_CHECK(!clusterList.hasCluster(clusters[n]));
    BOOST_CHECK(clusterList.addCluster(clusters[n]));
    BOOST_CHECK(clusterList.getCluster(clusters[n]->getName()));
    BOOST_CHECK(clusterList.hasCluster(clusters[n]));
    BOOST_CHECK_EQUAL(clusterList.getFirstCluster(), clusters[0]);
  }

  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(clusterList.getCluster(clusters[n]->getName()));
    BOOST_CHECK(clusterList.hasCluster(clusters[n]->getName()));
    BOOST_CHECK(clusterList.hasCluster(clusters[n]));
    BOOST_CHECK(!clusterList.addCluster(clusters[n]));
  }

  BOOST_CHECK_EQUAL(clusterCount, clusterList.size());
}

BOOST_AUTO_TEST_CASE(RoundClusterRemoveTest) {
  const size_t clusterCount = 10;

  Cluster *clusters[clusterCount];
  ClusterList clusterList;

  for (size_t n = 0; n < clusterCount; n++) {
    clusters[n] = new Cluster();
    std::stringstream clusterName;
    clusterName << "cluster" << n;
    clusters[n]->setName(clusterName.str());
  }

  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(clusterList.addCluster(clusters[n]));
  }
  BOOST_CHECK_EQUAL(clusterCount, clusterList.size());

  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(clusterList.removeCluster(clusters[n]));
    BOOST_CHECK_EQUAL((clusterCount - n - 1), clusterList.size());
  }
  BOOST_CHECK_EQUAL(0, clusterList.size());
}

BOOST_AUTO_TEST_CASE(RoundClusterRemoveByNameTest) {
  const size_t clusterCount = 10;

  Cluster *clusters[clusterCount];
  ClusterList clusterList;

  for (size_t n = 0; n < clusterCount; n++) {
    clusters[n] = new Cluster();
    std::stringstream clusterName;
    clusterName << "cluster" << n;

    clusters[n]->setName(clusterName.str());
  }

  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(clusterList.addCluster(clusters[n]));
  }
  BOOST_CHECK_EQUAL(clusterCount, clusterList.size());

  for (size_t n = 0; n < clusterCount; n++) {
    BOOST_CHECK(clusterList.removeCluster(clusters[n]->getName()));
    BOOST_CHECK_EQUAL((clusterCount - n - 1), clusterList.size());
  }
  BOOST_CHECK_EQUAL(0, clusterList.size());
}
