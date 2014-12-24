/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Cluster.h>

Round::Cluster::Cluster() {
}

Round::Cluster::Cluster(const std::string &name) {
  setName(name);
}

Round::Cluster::Cluster(const Cluster *cluster) {
  setName(cluster->getName());
}

Round::Cluster::~Cluster() {
}

bool Round::Cluster::equals(const Cluster *otherCluster) const {
  if (this->name.compare(otherCluster->getName()) == 0) {
    return true;
  }
  return false;
}
