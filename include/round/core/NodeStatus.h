/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODESTATUS_H_
#define _ROUNDCC_NODESTATUS_H_

#include <round/Const.h>

#define ROUNDCC_NODE_STATUS_STOP 1
#define ROUNDCC_NODE_STATUS_ACTIVATING 2
#define ROUNDCC_NODE_STATUS_ACTIVE 3
#define ROUNDCC_NODE_STATUS_TERMINATING 4
#define ROUNDCC_NODE_STATUS_PROMICE 5

namespace Round {
class NodeStatus {
 public:
  typedef enum State {
    UNKNOWN = ROUNDCC_NODE_STATUS_UNKNOWN,
    STOP = ROUNDCC_NODE_STATUS_STOP,
    ACTIVATING = ROUNDCC_NODE_STATUS_ACTIVATING,
    ACTIVE = ROUNDCC_NODE_STATUS_ACTIVE,
    PROMICE = ROUNDCC_NODE_STATUS_PROMICE,
    TERMINATING = ROUNDCC_NODE_STATUS_TERMINATING,
    STATE_MAX,
  } State;

 public:
  static const char *GetStateString(int state);

 public:
  NodeStatus();
  ~NodeStatus();

  void setState(State value) {
    this->nodeState = value;
  }

  bool setState(const std::string &valueString);

  State getState() const {
    return this->nodeState;
  }

  const char *getStateString() const;

private:

  State nodeState;

};

}

#endif
