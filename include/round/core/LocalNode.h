/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_LOCALNODE_H_
#define _ROUNDCC_LOCALNODE_H_

#include <round/common/Thread.h>
#include <round/core/Node.h>
#include <round/core/NodeGraph.h>
#include <round/core/NodeFinder.h>
#include <round/core/LocalNodeConfig.h>

namespace Round {

class LocalNode : public Node, public NodeFinderObserver, public NodeMessageListener {
 public:
  LocalNode();
  virtual ~LocalNode();

  bool loadConfigFromString(const std::string &string, Error *error);
  bool loadConfigFromFile(const std::string &filename, Error *error);
  bool isConfigValid(Error *error);
  
  bool nodeAdded(Node *node);
  bool nodeRemoved(Node *node);

  bool postMessage(const NodeRequest &reqMsg, NodeResponse *resMsg);
  bool nodeMessageReceived(const NodeRequest &reqMsg, NodeResponse *resMsg);

  bool waitMessage(Message *msg);
  bool execMessage(const Message *msg);

  virtual bool start(Error *error);
  virtual bool stop(Error *error);

  bool restart(Error *error);
  
  LocalNodeConfig *getNodeConfig() {
    return &this->nodeConfig;
  }

  NodeGraph *getNodeGraph() {
    return &this->nodeGraph;
  }
  
  bool isCloneable() const {
    return false;
  }
  
 protected:

  void setState(NodeStatus::State value) {
    this->nodeStatus.setState(value);
  }

  NodeStatus::State getState() {
    return this->nodeStatus.getState();
  }

private:

  void init();

private:

  LocalNodeConfig nodeConfig;
  NodeGraph nodeGraph;
  NodeStatus nodeStatus;

  NodeMessageManager msgManager;
  ThreadManager NodeOperation;
};

}

#endif
