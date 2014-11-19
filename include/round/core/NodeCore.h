/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODE_H_
#define _ROUNDCC_NODE_H_

#include <string>
#include <vector>

#include <round/common/ConsistentHash.h>
#include <round/common/Cloneable.h>
#include <round/common/Message.h>
#include <round/common/Dictionary.h>
#include <round/core/Cluster.h>
#include <round/core/ErrorNo.h>
#include <round/core/NodeStatus.h>

namespace Round {

class NodeCore : public ConsistentHashNode, public Cloneable<Node> {

 public:
  NodeCore();
  virtual ~NodeCore();

 public:

  virtual int getRequestPort() const = 0;
  virtual const char *getRequestAddress() const = 0;
  virtual bool postMessage(const Message *msg) = 0;

 public:

  const char *getHashSeed(std::string *seedString) const;
};

}

#endif
