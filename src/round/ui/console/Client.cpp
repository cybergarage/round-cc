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

Round::Console::Client::Client() {
  init();
}

Round::Console::Client::~Client() {
}

void Round::Console::Client::init() {
  initOptions();
  initCommands();
}

void Round::Console::Client::initOptions() {
  
}

void Round::Console::Client::initCommands() {
  
}

void Round::Console::Client::setProgramNameFromArgument(const std::string &argValue)
{
  this->promptName = argValue;
  size_t lastPathIndex = this->promptName.find_last_of("/");
  if (lastPathIndex != std::string::npos)
    this->promptName = this->promptName.substr((lastPathIndex + 1));
  this->promptName = this->promptName;
  this->promptName.append("> ");
}

struct roundcc_tocapital {
  bool isFirstChar;
  roundcc_tocapital(){
    isFirstChar = true;
  }
  int operator()(int c) {
    if (isFirstChar) {
      isFirstChar = false;
      return toupper(c);
    }
    return tolower(c);
  }
};

const char *Round::Console::Client::getBootMessage(std::string &buffer)
{
  std::stringstream bootMsg;
  bootMsg << ROUNDCC_PRODUCT_NAME << " " << ROUNDCC_PRODUCT_VERSION;
  buffer = bootMsg.str();

  std::transform(buffer.begin(), buffer.end(), buffer.begin(), roundcc_tocapital());

  return buffer.c_str();
}

const char *Round::Console::Client::getProgramName()
{
  return promptName.c_str();
}

const char *Round::Console::Client::getPromptName()
{
  return promptName.c_str();
}

bool Round::Console::Client::isConsoleCommand(const std::string &inputLine) {
  return false;
}

bool Round::Console::Client::isConsoleQuitCommand(const std::string &inputLine) {
  return false;
}

bool Round::Console::Client::execConsoleCommand(const std::string &inputLine,  Message *msg, Error *err) {
  return false;
}
