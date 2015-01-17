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

const std::string Round::Console::Command::QUIT = "quit";
const std::string Round::Console::Command::EXIT = "exit";
const std::string Round::Console::Command::LIST = "list";
const std::string Round::Console::Command::USE = "use";
const std::string Round::Console::Command::CLUSTERS = "clusters";
const std::string Round::Console::Command::NODES = "nodes";

Round::Console::Command::Command()
{
}

Round::Console::Command::~Command()
{
}

std::string Round::Console::Command::GetCommand(const std::string &inputLine) {
  size_t lastExtraIndex = inputLine.find_last_not_of(" \n");
  std::string lowerInputLine = (lastExtraIndex == std::string::npos) ? inputLine : (std::string(inputLine, 0, (lastExtraIndex + 1)));
  std::transform(lowerInputLine.begin(), lowerInputLine.end(), lowerInputLine.begin(), ::tolower);
  return lowerInputLine;
}

bool Round::Console::Command::isCommand(const std::string &inputLine) {
  std::string cmd = GetCommand(inputLine);
  return (cmd.find_first_of(this->name) == 0) ? true : false;
}
