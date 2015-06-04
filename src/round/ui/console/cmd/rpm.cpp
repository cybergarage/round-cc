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

const std::string Round::Console::rpm::NAME = "rpm";

const std::string Round::Console::rpm::getDescription() const {
  return "Manges package";
}

const std::string Round::Console::rpm::getOptionDescription() const {
  return "<command> <params>";
}

bool Round::Console::rpm::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  return false;
}
