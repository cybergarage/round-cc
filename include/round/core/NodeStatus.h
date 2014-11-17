/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODESTATUS_H_
#define _ROUNDCC_NODESTATUS_H_


namespace Round {
class NodeStatus {
 public:
  typedef enum State {
    UNKNOWN = 0,
    STOP,
    ACTIVATING,
    ACTIVE,
    REPAIRING,
    OPTIMIZING,
    FINALIZING,
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
