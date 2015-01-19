/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/ui/console/Command.h>

const std::string Round::Console::update::NAME = "update";

const std::string Round::Console::update::getDescription() const {
  return "Update current clusters and nodes";
}

bool Round::Console::update::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  return true;
}
