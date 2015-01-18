/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string.hpp>
#include <round/ui/Console.h>

const std::string Round::Console::Command::QUIT = "quit";
const std::string Round::Console::Command::EXIT = "exit";
const std::string Round::Console::Command::SHELL = "shell";

Round::Console::Command::Command(const std::string &name)
{
  this->name = name;
}

Round::Console::Command::~Command()
{
}

bool Round::Console::Command::IsCommand(const std::string &name, const Input *input) {
  return (name.compare(input->cmd) == 0) ? true : false;
}

bool Round::Console::Command::isCommand(const Input *input) {
  return IsCommand(this->name, input);
}

bool Round::Console::Command::IsQuit(const Input *input) {
  if (IsCommand(QUIT, input))
    return true;
  if (IsCommand(EXIT, input))
    return true;
  return false;
}

bool Round::Console::Command::IsShell(const Input *input) {
  return IsCommand(SHELL, input);
}
