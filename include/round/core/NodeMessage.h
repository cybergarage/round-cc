/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEMESSAGE_H_
#define _ROUNDCC_NODEMESSAGE_H_

#include <round/common/Message.h>

namespace Round {

class NodeMessage : public Message {
 public:
  NodeMessage();
  virtual ~NodeMessage();
};

class NodeRequest : public NodeMessage {
 public:
  static const std::string KEY_METHOD;
    
 public:
  NodeRequest();
  virtual ~NodeRequest();
};
  
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
