/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_CLUSTER_H_
#define _ROUNDCC_CLUSTER_H_

#include <vector>
#include <string>

#include <round/core/NodeGraph.h>

namespace Round {

class Cluster  {

 public:
  Cluster();
  Cluster(const Cluster *cluster);
  Cluster(const std::string &value);

  virtual ~Cluster();

  void setName(const std::string &value) {
    this->name = value;
  }

  const char *getName() const {
    return this->name.c_str();
  }

  bool isName(const std::string &value) {
    return (this->name.compare(value) == 0) ? true : false;
  }

  bool equals(const Cluster *otherCluster);

  bool equals(const Cluster otherCluster) {
    return equals(&otherCluster);
  }
  
  NodeGraph *getNodeGraph() {
    return &this->nodeGraph;
  }

private:

  std::string name;
  NodeGraph nodeGraph;
};

class ClusterList : public std::vector<Cluster *> {
  
 public:
  
  ClusterList();
  virtual ~ClusterList();

  bool addCluster(Cluster *cluster);

  Cluster *getCluster(size_t index) const {
    return at(index);
  }

  Cluster *getFirstCluster() const {
    if (size() <= 0)
      return NULL;
    return at(0);
  }
  
  Cluster *getCluster(const std::string &name);

  bool hasCluster(Cluster *cluster);
  bool hasCluster(const std::string &name);

  bool removeCluster(Cluster *cluster);
  bool removeCluster(const std::string &name);
};

}

#endif
