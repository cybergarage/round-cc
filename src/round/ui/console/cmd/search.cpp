/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>
#include <round/ui/console/Command.h>

const std::string Round::Console::search::NAME = ROUNDCC_SCRIPT_SEARCH_METHOD;

const std::string Round::Console::search::getDescription() const {
  return "Search new clusters and nodes";
}

bool Round::Console::search::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  bool isSuccess = client->search(err);
  waitAnimation(ROUNDCC_SCRIPT_SEARCH_METHOD_WAIT_MSEC, ROUNDCC_MESSAGE_SEARCHING);
  return isSuccess;
}
