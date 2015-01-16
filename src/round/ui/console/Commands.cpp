/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/ui/Console.h>

Round::Console::Commands::Commands()
{
}

Round::Console::Commands::~Commands()
{
}

bool Round::Console::Commands::hasCommand(const std::string &inputLine) {
  std::string cmd = Command::GetCommand(inputLine);
  return (find(cmd) != Commands::end()) ? true : false;
}

bool Round::Console::Commands::execCommand(Round::Client *client, const std::string &inputLine, Message *msg, Error *err) {
  std::string cmd = Command::GetCommand(inputLine);
  Commands::iterator cmdIt = find(cmd);
  if (cmdIt == Commands::end()) {
  }
  return false;
}
