/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEREQUEST_H_
#define _ROUNDCC_NODEREQUEST_H_

#include <round/core/NodeMessage.h>

namespace Round {

class NodeRequest : public NodeMessage {
 public:
  static const std::string KEY_METHOD;
  
 public:
  NodeRequest();
  virtual ~NodeRequest();
};

}

#endif
