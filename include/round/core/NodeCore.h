/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODECORE_H_
#define _ROUNDCC_NODECORE_H_

#include <string>
#include <vector>
  
#include <round/common/ConsistentHash.h>
#include <round/common/Clock.h>
#include <round/core/NodeMessage.h>

namespace Round {

class NodeCore : public ConsistentHashNode {

 public:
  NodeCore();
  virtual ~NodeCore();

 public:

  virtual bool getRequestAddress(std::string *address, Error *error) const = 0;
  virtual bool getRequestPort(int *port, Error *error) const = 0;
  virtual bool getClusterName(std::string *name, Error *error) = 0;
  
  virtual bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) = 0;

 public:

  clock_t getClock() const;

  const char *getHashSeed(std::string *seedString) const;

 private:
  Clock clock;
};

}

#endif
