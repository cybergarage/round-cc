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
  static const std::string KEY_CLOCK;
  
 public:
  NodeMessage();
  virtual ~NodeMessage();
};

class NodeRequest : public NodeMessage {
 public:
  static const std::string KEY_METHOD;
    
 public:
  NodeRequest(const std::string &method);
  virtual ~NodeRequest();
  
  bool hasMethod() const;
  bool isMethod(const std::string &method) const;
};

class NodeResponse : public NodeMessage {
public:
  static const std::string KEY_ERROR_CODE;
  static const std::string KEY_ERROR_MESSAGE;
    
public:
  NodeResponse();
  virtual ~NodeResponse();
};
  
}

#endif
