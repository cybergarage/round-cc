/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/RPC.h>

const std::string Round::RPC::JSON::Message::JSON_RPC = "jsonrpc";
const std::string Round::RPC::JSON::Message::METHOD = "method";
const std::string Round::RPC::JSON::Message::PARAMS = "params";
const std::string Round::RPC::JSON::Message::ID = "id";
const std::string Round::RPC::JSON::Message::ERROR = "error";
const std::string Round::RPC::JSON::Message::CODE = "code";
const std::string Round::RPC::JSON::Message::MESSAGE = "message";
const std::string Round::RPC::JSON::Message::RESULT = "result";

const std::string Round::RPC::JSON::Message::TIMESTAMP = "ts";
const std::string Round::RPC::JSON::Message::HASH = "hash";

const std::string Round::RPC::JSON::Message::DEST = "dest";
const std::string Round::RPC::JSON::Message::DEST_ONE = "one";
const std::string Round::RPC::JSON::Message::DEST_ALL = "all";

Round::RPC::JSON::Message::Message() {
}

Round::RPC::JSON::Message::~Message() {
}

bool Round::RPC::JSON::Message::isDestValid() const {
  if (!hasDest())
    return true;
  if (isDestOne())
    return true;
  if (isDestAll())
    return true;
  if (isDestQuorum())
    return true;
  return false;
}

bool Round::RPC::JSON::Message::isDestOne() const {
  if (!hasDest())
    return false;
  std::string dest;
  if (!getDest(&dest))
    return false;
  return (dest.compare(DEST_ONE) == 0) ? true : false;
}

bool Round::RPC::JSON::Message::isDestAll() const {
  if (!hasDest())
    return false;
  std::string dest;
  if (!getDest(&dest))
    return false;
  return (dest.compare(DEST_ALL) == 0) ? true : false;
}

bool Round::RPC::JSON::Message::isDestQuorum() const {
  if (!hasDest())
    return false;
  size_t quorum;
  if (!get(DEST, &quorum))
    return false;
  return (0 < quorum) ? true : false;
}

bool Round::RPC::JSON::Message::getQuorum(size_t *value) const {
  if (!isDestQuorum())
    return false;
  return get(DEST, value);
}
