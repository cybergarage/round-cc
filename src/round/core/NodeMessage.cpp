/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/NodeMessage.h>

const Round::NodeMessageType Round::NodeMessage::UNKNOWN = 0;
const Round::NodeMessageType Round::NodeMessage::TABLET  = 0x0100;
const Round::NodeMessageType Round::NodeMessage::TABLET_PUT  = TABLET + 1;
const Round::NodeMessageType Round::NodeMessage::TABLET_DELETE = TABLET + 2;

const std::string Round::NodeMessage::KEY_TYPE = "msgtype";
const std::string Round::NodeMessage::KEY_DB_SPACE = "dbspace";
const std::string Round::NodeMessage::KEY_DB_KEY = "dbkey";
const std::string Round::NodeMessage::KEY_DB_VALUE = "dbvalue";
const std::string Round::NodeMessage::KEY_OPT_REPLICATION = "optrep";

Round::NodeMessage::NodeMessage() {}

Round::NodeMessage::~NodeMessage() {}

bool Round::NodeMessage::set(const Round::NodeMessageType &type) {
  return Round::JSONDictionary::set(KEY_TYPE, type);
}
