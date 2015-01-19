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

const std::string Round::Console::help::getDescription() const {
  return "Show this help message";
}

bool Round::Console::help::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  
  size_t cmdNameMaxLen = 0;
  for (Commands::iterator cmdIt=client->commands.begin(); cmdIt != client->commands.end(); cmdIt++) {
    Command *cmd = cmdIt->second;
    std::string option = cmd->getOptionDescription();
    size_t cmdNameLen = cmd->name.length() + option.length() + 1;
    if (cmdNameMaxLen < cmdNameLen) {
      cmdNameMaxLen = cmdNameLen;
    }
  }
  
  for (Commands::iterator cmdIt=client->commands.begin(); cmdIt != client->commands.end(); cmdIt++) {
    Command *cmd = cmdIt->second;
    size_t outputLen = cmd->name.length();
    std::cout << cmd->getName();
    std::string option = cmd->getOptionDescription();
    if (0 < option.length()) {
      std::cout << " " << option;
      outputLen += option.length() + 1;
    }
    for (size_t n=0; n<(cmdNameMaxLen-outputLen); n++) {
      std::cout << " ";
    }
    std::cout << " " << cmd->getDescription() << std::endl;
  }
  return true;
}
