/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
const std::string Round::RPC::JSON::Message::QUORUM = "quorum";

const std::string Round::RPC::JSON::Message::DEST = "dest";
const std::string Round::RPC::JSON::Message::DEST_ANY = ROUNDCC_SYSTEM_METHOD_DEST_ANY_NODE;
const std::string Round::RPC::JSON::Message::DEST_ALL = ROUNDCC_SYSTEM_METHOD_DEST_ALL_NODE;

const std::string Round::RPC::JSON::Message::TYPE = "type";
const std::string Round::RPC::JSON::Message::COND = "cond";
const std::string Round::RPC::JSON::Message::DIGEST = "digest";

Round::RPC::JSON::Message::Message() {
}

Round::RPC::JSON::Message::~Message() {
}

bool Round::RPC::JSON::Message::setDestAny() {
  return setDest(DEST_ANY);
}

bool Round::RPC::JSON::Message::setDestAll() {
  return setDest(DEST_ALL);
}

bool Round::RPC::JSON::Message::IsDestAny(const std::string &dest) {
  return (dest.compare(DEST_ANY) == 0) ? true : false;
}

bool Round::RPC::JSON::Message::IsDestAll(const std::string &dest) {
  return (dest.compare(DEST_ALL) == 0) ? true : false;
}

bool Round::RPC::JSON::Message::IsDestHash(const std::string &dest) {
  return HashObject::IsHashCode(dest);
}

bool Round::RPC::JSON::Message::isDestValid() const {
  if (!hasDest())
    return true;
  if (isDestAll())
    return true;
  if (isDestAny())
    return true;
  return isDestHash();
}

bool Round::RPC::JSON::Message::setDest(HashObject *hashObj) {
  std::string hashCode;
  if (!hashObj->getHashCode(&hashCode))
    return false;
  return setDest(hashCode);
}

bool Round::RPC::JSON::Message::isDestAll() const {
  if (!hasDest())
    return false;
  std::string dest;
  if (!getDest(&dest))
    return false;
  return IsDestAll(dest);
}

bool Round::RPC::JSON::Message::isDestAny() const {
  if (!hasDest())
    return false;
  std::string dest;
  if (!getDest(&dest))
    return false;
  return IsDestAny(dest);
}

bool Round::RPC::JSON::Message::isDestHash() const {
  if (!hasDest())
    return false;
  std::string dest;
  if (!getDest(&dest))
    return false;
  return IsDestHash(dest);
}

bool Round::RPC::JSON::Message::isDestOne() const {
  if (!hasDest())
    return true;
  if (isDestAny())
    return true;
  if (isDestAll())
    return false;
  return isDestHash();
}
