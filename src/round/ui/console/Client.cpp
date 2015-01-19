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

bool Round::Console::Client::isConsoleCommand(const Input &input) {
  return this->commands.hasCommand(&input);
}

bool Round::Console::Client::isRPCCommand(const Input &input) {
  size_t paramBeginIdx = input.line.find_first_of(rpc::PARAM_BEGIN);
  if (paramBeginIdx == std::string::npos)
    return false;
  size_t paramEndIdx = input.line.find_first_of(rpc::PARAM_END);
  if (paramEndIdx == std::string::npos)
    return false;
  return (paramBeginIdx < paramEndIdx) ? true : false;
}

bool Round::Console::Client::isQuitCommand(const Input &input) {
  return Command::IsQuit(&input);
}

bool Round::Console::Client::isShellCommand(const Input &input) {
  return Command::IsShell(&input);
}

bool Round::Console::Client::execConsoleCommand(const Input &input, Message *msg, Error *err) {
  return this->commands.execCommand(this, &input, msg, err);test(22,222)
}

bool Round::Console::Client::execRPCCommand(const Input &input, Message *msg, Error *err) {
  Command *cmd = this->commands.getCommand(rpc::NAME);
  if (!cmd)
    return false;
  return cmd->exec(this, &input, msg, err);
}

bool Round::Console::Client::usage() {
  Command *help = this->commands.getCommand(Round::Console::help::NAME);
  if (!help)
    return false;

  std::cout << "Usage: " << getProgramName() << " [-options] <command>" << std::endl;
  std::cout << std::endl;
  help->exec(this, NULL, NULL, NULL);
  std::cout << std::endl;
  for (Options::iterator optIt=options.begin(); optIt != options.end(); optIt++) {
    Option *opt = optIt->second;
    std::cout << "-" << opt->getId() << Command::TAB << opt->getDescription() << std::endl;
  }
  
  return true;
}
