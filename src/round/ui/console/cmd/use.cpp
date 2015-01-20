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
#include <round/common/RPC.h>

const std::string Round::Console::use::NAME = "use";
const std::string Round::Console::use::ERROR_CLUSTER_NOTSPECFIED = "Cluster not specified";
const std::string Round::Console::use::ERROR_CLUSTER_NOTFOUND = "Cluster not found";

const std::string Round::Console::use::getDescription() const {
  return "Select cluster";
}

const std::string Round::Console::use::getOptionDescription() const {
  return "<cluster>";
}

bool Round::Console::use::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  if (input->params.size() <= 0) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(ERROR_CLUSTER_NOTSPECFIED);
  }

  if (!client->setTargetCluster(input->params[0])) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInvalidParams, err);
    err->setDetailMessage(ERROR_CLUSTER_NOTFOUND);
    return false;
  }
  
  return true;
}
