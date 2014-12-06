/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Log.h>
#include <round/core/RemoteNode.h>
#include <round/core/NodeGraph.h>

#include <uhttp/net/Socket.h>

Round::RemoteNode::RemoteNode(const Round::Node *node) {
  this->requestAddress = node->getRequestAddress();
  this->requestPort = node->getRequestPort();
}

Round::RemoteNode::RemoteNode(const std::string &address, int port) {
  this->requestAddress = address;
  this->requestPort = port;
}

Round::RemoteNode::~RemoteNode() {
}

bool Round::RemoteNode::postMessage(const NodeRequest *reqMsg, NodeResponse *resMsg) {
  return false;
}

Round::Node *Round::RemoteNode::clone() const {
  return new RemoteNode(this);
}
