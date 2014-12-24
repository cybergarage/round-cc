/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_TESTLIENT_H_
#define _ROUNDCC_TESTLIENT_H_

#include <round/Client.h>

#include "RoundTest.h"

class TestClient : public Round::Client {
public:
  TestClient() {
  }

  const Round::ClusterList *getClusters() const {
    return Round::Client::getClusters();
  }
  
  size_t getClusterCount() const {
    return Round::Client::getClusterCount();
  }
  
  bool setTargetCluster(const std::string &clusterName) {
    return Round::ClientCore::setTargetCluster(clusterName);
  }
};

class TestClientCore : public Round::ClientCore {
 public:
  TestClientCore() {
  }
  
  bool addCuster(const std::string &clusterName) {
    return Round::ClientCore::addCluster(clusterName);
  }
};

#endif
