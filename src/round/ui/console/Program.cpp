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
#include <vector>
#include <string>

#include <round/Round.h>
#include <round/ui/Console.h>
#include <round/ui/console/Command.h>

Round::Console::Program::Program() {
  init();
}

Round::Console::Program::~Program() {
}

void Round::Console::Program::init() {
  initOptions();
}

void Round::Console::Program::initOptions() {
  
}

void Round::Console::Program::setProgramNameFromArgument(const std::string &argValue)
{
  this->programName = argValue;
  size_t lastPathIndex = this->programName.find_last_of("/");
  if (lastPathIndex != std::string::npos)
    this->programName = this->programName.substr((lastPathIndex + 1));
}

const char *Round::Console::Program::getProgramName()
{
  return programName.c_str();
}

void Round::Console::Program::printOptions() {
  for (Options::iterator optIt=options.begin(); optIt != options.end(); optIt++) {
    Option *opt = optIt->second;
    std::cout << "-" << opt->getId() << Command::TAB << opt->getDescription() << std::endl;
  }
}
