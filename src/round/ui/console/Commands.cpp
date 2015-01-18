/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/ui/Console.h>
#include <round/ui/console/Command.h>

Round::Console::Commands::Commands()
{
  init();
}

Round::Console::Commands::~Commands()
{
}

void Round::Console::Commands::init() {
  addCommand(new list());
}

bool Round::Console::Commands::addCommand(Command *cmd) {
  std::string name = cmd->getName();
  insert(std::pair<std::string, Command *>(name, cmd));
  return true;
}

bool Round::Console::Commands::hasCommand(const Input *input) const {
  return (find(input->cmd) != Commands::end()) ? true : false;
}

bool Round::Console::Commands::execCommand(Round::Client *client, const Input *input, Message *msg, Error *err) const {
  Commands::const_iterator cmdIt = find(input->cmd);
  if (cmdIt == Commands::end())
    return false;
  return (cmdIt->second)->exec(client, &input->params, msg, err);
}

