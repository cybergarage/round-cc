/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODMESSAGE_H_
#define _ROUNDCC_NODMESSAGE_H_

#include <round/common/Message.h>
#include <round/core/Node.h>

namespace Round {
  
typedef int NodeMessageType;

class NodeMessage : public Message {
 public:
  static const NodeMessageType UNKNOWN;
  static const NodeMessageType TABLET;
  static const NodeMessageType TABLET_PUT;
  static const NodeMessageType TABLET_DELETE;

  static const std::string KEY_TYPE;

  static const std::string KEY_DB_SPACE;
  static const std::string KEY_DB_KEY;
  static const std::string KEY_DB_VALUE;

  static const std::string KEY_OPT_REPLICATION;

 public:
  NodeMessage();
  virtual ~NodeMessage();

  bool set(const NodeMessageType &type);
};

}

#endif
