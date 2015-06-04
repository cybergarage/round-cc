/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/common/Thread.h>
#include <round/core/local/method/SystemMethod.h>

const std::string Round::remove_node::NAME = ROUNDCC_SYSTEM_METHOD_REMOVE_NODE;

namespace Round {

class remove_node_task : public Thread<LocalNode> {
public:
  remove_node_task() {}

  void run() {
    sleep(ROUNDCC_SYSTEM_METHOD_REMOVE_NODE_DELAY_MSEC);
    
    Error err;
    LocalNode *node = getObject();
    node->stop(&err);
    delete this;
  }
};

}

Round::remove_node::remove_node() : system_method(NAME) {
}

Round::remove_node::~remove_node() {
}

bool Round::remove_node::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  remove_node_task *task = new remove_node_task();
  return task->start();
}
