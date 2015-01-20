/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/Round.h>
#include <round/ui/console/Command.h>
#include <round/core/RQL.h>

const std::string Round::Console::rpc::NAME = "method(<obj>, <params>)";
const std::string Round::Console::rpc::PARAM_BEGIN = "(";
const std::string Round::Console::rpc::PARAM_END = ")";
const std::string Round::Console::rpc::PARAM_SEP = ",";
const std::string Round::Console::rpc::OBJECT_SEP = ".";

const std::string Round::Console::rpc::getDescription() const {
  return "Execute RPC method";
}

const std::string Round::Console::rpc::getOptionDescription() const {
  return "";
}

bool Round::Console::rpc::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  std::cout << "RPC : " << input->line << std::endl;
  
  RQLRequest rqlReq;
  if (!rqlReq.parseQuery(input->line,err))
    return false;

  NodeResponse nodeRes;
  if (client->postMessage(&rqlReq, &nodeRes, err)) {
    std::string result;
    if (nodeRes.getResult(&result)) {
      *msg = result;
    }
    return true;
  }
  
  return false;
}
