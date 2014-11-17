/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODERESPONSE_H_
#define _ROUNDCC_NODERESPONSE_H_

#include <round/core/NodeMessage.h>

namespace Round {
  
class NodeResponse : public NodeMessage {
 public:
  static const std::string KEY_CODE;
  static const std::string KEY_DETAILCODE;
  
 public:
  NodeResponse();
  virtual ~NodeResponse();
};

}

#endif
