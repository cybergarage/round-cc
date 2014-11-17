/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>

#include <round/core/NodeStatus.h>

Round::NodeStatus::NodeStatus() {
  setState(UNKNOWN);
}

Round::NodeStatus::~NodeStatus() {
}

bool Round::NodeStatus::setState(const std::string &valueString) {
  for (int n = 0; n < STATE_MAX; n++) {
    if (valueString.compare(GetStateString(n)) == 0) {
      setState((State)n);
      return true;
    }
  }

  setState(UNKNOWN);
  
  return false;
}

const char *Round::NodeStatus::GetStateString(int status) {
  switch(status) {
  case STOP:
    return "stop";
  case ACTIVATING:
    return "activating";
  case ACTIVE:
    return "active";
  case REPAIRING:
    return "repairing";
  case OPTIMIZING:
    return "optimizing";
  case FINALIZING:
    return "finalizing";
  }  
  
  return "unknown";
}

const char *Round::NodeStatus::getStateString() const {
  return GetStateString(getState());
}
