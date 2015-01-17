/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <algorithm>

#include <round/core/Cluster.h>

Round::ClusterList::ClusterList() {
}

Round::ClusterList::~ClusterList() {
  clear();
}

bool Round::ClusterList::addCluster(Cluster *cluster) {
  if (hasCluster(cluster)) {
    return false;
  }
  push_back(cluster);
  return true;
}

bool Round::ClusterList::hasCluster(Cluster *otherCluster) const {
  for (ClusterList::const_iterator cluster = begin(); cluster != end(); cluster++) {
    if ((*cluster)->equals(otherCluster)) {
      return true;
    }
  }
  return false;
}

bool Round::ClusterList::hasCluster(const std::string &name) const {
  for (ClusterList::const_iterator cluster = begin(); cluster != end(); cluster++) {
    if ((*cluster)->isName(name)) {
      return true;
    }
  }
  return false;
}

Round::Cluster *Round::ClusterList::getCluster(const std::string &name) const {
  for (ClusterList::const_iterator cluster = begin(); cluster != end(); cluster++) {
    if ((*cluster)->isName(name)) {
      return (*cluster);
    }
  }
  return NULL;
}

bool Round::ClusterList::removeCluster(Cluster *otherCluster) {
  size_t clusterSize = size();
  erase(std::remove(begin(), end(), otherCluster), end());
  return (size() < clusterSize) ? true : false;
}

bool Round::ClusterList::removeCluster(const std::string &name) {
  Cluster *foundCluster = NULL;

  for (ClusterList::iterator cluster = begin(); cluster != end(); cluster++) {
    if ((*cluster)->isName(name)) {
      foundCluster = (*cluster);
      break;
    }
  }

  if (!foundCluster)
    return false;

  return removeCluster(foundCluster);
}

bool Round::ClusterList::clear() {
  for (ClusterList::iterator cluster = begin(); cluster != end(); cluster++) {
    delete *cluster;
  }
  std::vector<Cluster *>::clear();
  return true;
}


