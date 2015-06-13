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

const std::string Round::Console::daemon::NAME = "daemon";

const std::string Round::Console::daemon::getDescription() const {
  return "Run as daemon";
}

bool Round::Console::daemon::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  return true;
}