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

Round::Console::Server::Server() {
}

Round::Console::Server::~Server() {
}

void Round::Console::Server::initOptions() {
  addOption(new Option('f', "", "Runs in foreground mode"));
  addOption(new Option('v', "", "Enables verbose output"));
  addOption(new Option('h', "", "Prints this help message"));
  addOption(new Option('p', "<port number>", "Runs HTTP server on given port"));
  addOption(new Option('c', "<filename>", "Specifies a configuration file"));
}

void Round::Console::Server::usage() {
  std::cout << "Usage: " << getProgramName() << " [-options]" << std::endl;
  std::cout << std::endl;
  printOptions();
}
