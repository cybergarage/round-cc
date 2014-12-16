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

Round::RPC::JSON::Message::Message() {
}

Round::RPC::JSON::Message::~Message() {
}
