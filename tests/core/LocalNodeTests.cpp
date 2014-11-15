/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string.h>

#include <round/Round.h>

#include "RoundTest.h"
#include "TestNode.h"

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_CASE(LocalNodeConfigTest) {
  TestLocalNode localNode;
  Error err;

  std::string version;
  BOOST_CHECK(localNode.getVersion(&version, &err));
  BOOST_CHECK(0 < version.length());

  Cluster cluster;
  std::string clusterName;
  BOOST_CHECK(localNode.getCluster(&cluster, &err));
  clusterName = cluster.getName();
  BOOST_CHECK(0 < clusterName.length());
}

BOOST_AUTO_TEST_CASE(LocalNodeEqualTest) {
  TestLocalNode localNode01("192.168.0.1", 80);
  TestLocalNode localNode02("192.168.0.1", 80);
  TestLocalNode localNode03("192.168.0.2", 80);
  TestLocalNode localNode04("192.168.0.1", 81);
  TestLocalNode localNode05("192.168.0.2", 81);

  BOOST_CHECK(localNode01.equals(&localNode01));
  BOOST_CHECK(localNode01.equals(&localNode02));
  BOOST_CHECK(!localNode01.equals(&localNode03));
  BOOST_CHECK(!localNode01.equals(&localNode04));
  BOOST_CHECK(!localNode01.equals(&localNode05));
}
