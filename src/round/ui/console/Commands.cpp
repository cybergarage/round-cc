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
  clear();
}

void Round::Console::Commands::init() {
  // real commands
  addCommand(new shell());
  addCommand(new help());
  addCommand(new list());
  addCommand(new search());
  addCommand(new update());
  addCommand(new version());
  addCommand(new quit());
  addCommand(new verbose());
  addCommand(new use());
  addCommand(new rpm());

  // alias commands
  addCommand(new exit());
  addCommand(new question());

  // RPC method
  addCommand(new method());
}

void Round::Console::Commands::clear() {
  for (Commands::iterator cmdId = begin(); cmdId != end(); cmdId++) {
    delete cmdId->second;
  }
  std::map<std::string, Command*>::clear();
}

bool Round::Console::Commands::addCommand(Command *cmd) {
  std::string name = cmd->getName();
  insert(std::pair<std::string, Command *>(name, cmd));
  return true;
}

bool Round::Console::Commands::isNonExecutedCommand(const Input *input) const {
  if (input->cmd.compare(method::NAME) == 0)
    return true;
  return false;
}

bool Round::Console::Commands::hasCommand(const Input *input) const {
  if (isNonExecutedCommand(input))
    return false;
  return (find(input->cmd) != Commands::end()) ? true : false;
}

Round::Console::Command *Round::Console::Commands::getCommand(const std::string &name) const {
  Commands::const_iterator cmdIt = find(name);
  if (cmdIt == Commands::end())
    return NULL;
  return cmdIt->second;
}

bool Round::Console::Commands::execCommand(Client *client, const Input *input, Message *msg, Error *err) const {
  if (isNonExecutedCommand(input))
    return false;
  Commands::const_iterator cmdIt = find(input->cmd);
  if (cmdIt == Commands::end())
    return false;
  return (cmdIt->second)->exec(client, input, msg, err);
}
