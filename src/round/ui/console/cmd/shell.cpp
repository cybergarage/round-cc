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

const std::string Round::Console::shell::NAME = "shell";

const std::string Round::Console::shell::getDescription() const {
  return "Run as interactive shell";
}

bool Round::Console::shell::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  return true;
}