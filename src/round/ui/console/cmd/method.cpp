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

const std::string Round::Console::method::NAME = "method";
const std::string Round::Console::method::PARAM_BEGIN = "(";
const std::string Round::Console::method::PARAM_END = ")";
const std::string Round::Console::method::PARAM_SEP = ",";
const std::string Round::Console::method::OBJECT_SEP = ".";
const std::string Round::Console::method::ERROR_CLUSTER_NOTFOUND = "Cluster not found";
const std::string Round::Console::method::ERROR_NODE_NOTFOUND = "Node not found";
const std::string Round::Console::method::ERROR_OBJECT_NOTSPECEFIED = "Node not specified";

const std::string Round::Console::method::getDescription() const {
  return "Execute RPC method";
}

const std::string Round::Console::method::getOptionDescription() const {
  return "(<obj>, <params>)";
}

bool Round::Console::method::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
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
