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

const std::string Round::Console::list::NAME = "list";

bool Round::Console::list::exec(Round::Client *client, const Params *params, Message *msg, Error *err) const {
  return true;
}
