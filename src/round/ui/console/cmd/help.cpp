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

const std::string Round::Console::help::NAME = "help";

bool Round::Console::help::exec(Round::Console::Client *client, const Params *params, Message *msg, Error *err) const {
  for (Commands::iterator cmdIt=client->commands.begin(); cmdIt != client->commands.end(); cmdIt++) {
    Command *cmd = cmdIt->second;
    std::cout << cmd->getName() << TAB << cmd->getDescription() << std::endl;
  }
  return true;
}

const std::string Round::Console::help::getDescription() const {
  return "Show this help message";
}
