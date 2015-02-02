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

Round::Console::Options::Options()
{
  init();
}

Round::Console::Options::~Options()
{
  clear();
}

void Round::Console::Options::init() {
}

void Round::Console::Options::clear() {
  for (Options::iterator optIt = begin(); optIt != end(); optIt++) {
    delete optIt->second;
  }
  std::map<char, Option*>::clear();
}

bool Round::Console::Options::addOption(Option *opt) {
  char type = opt->getId();
  insert(std::pair<char, Option *>(type, opt));
  return true;
}

