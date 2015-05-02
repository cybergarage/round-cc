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
#include <boost/thread.hpp>
#include <round/ui/Console.h>

const std::string Round::Console::Command::TAB = "    ";
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

void Round::Console::Command::sleep(int msec) const {
  boost::this_thread::sleep(boost::posix_time::milliseconds(msec));
}

void Round::Console::Command::waitAnimation(int msec) const {
  const int WAIT_SLEEP = 100;
  char waitChars[] = "-\\|/-\\|/";
  
  int loopCount = (msec / (WAIT_SLEEP * sizeof(waitChars))) + 1;
  for (int i=0; i<loopCount; i++) {
    std::string countHeader;
    for (int n=0; n<i; n++) {
      countHeader += ".";
    }
    for (int j=0; j<sizeof(waitChars); j++) {
      std::cout << "\r" << countHeader << waitChars[j] << std::flush; sleep(WAIT_SLEEP);
    }
  }
  
  std::string countHeader;
  for (int n=0; n<(loopCount+1); n++) {
    countHeader += ".";
  }
  std::cout << "\r" << countHeader << std::endl;
}
