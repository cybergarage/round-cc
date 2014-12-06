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
#include <round/core/NodeMessage.h>

namespace Round {

class NodeCore : public ConsistentHashNode {

 public:
  NodeCore();
  virtual ~NodeCore();

 public:

  virtual int getRequestPort() const = 0;
  virtual const char *getRequestAddress() const = 0;

  virtual bool postMessage(const NodeRequest *nodeReq, NodeResponse *nodeRes, Error *error) = 0;

 public:

  const char *getHashSeed(std::string *seedString) const;
};

}

#endif
