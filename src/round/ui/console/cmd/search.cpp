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

const std::string Round::Console::search::NAME = "search";

bool Round::Console::search::exec(Round::Console::Client *client, const Params *params, Message *msg, Error *err) const {
  return client->search(err);
}

const std::string Round::Console::search::getDescription() const {
  return "Search new clusters and nodes";
}
