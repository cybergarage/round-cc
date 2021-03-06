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
  initCommands();
  initOptions();
}

void Round::Console::Client::initCommands() {
  // real commands
  addCommand(new Round::Console::shell());
  addCommand(new Round::Console::help());
  addCommand(new Round::Console::list());
  addCommand(new Round::Console::search());
  addCommand(new Round::Console::update());
  addCommand(new Round::Console::version());
  addCommand(new Round::Console::quit());
  addCommand(new Round::Console::verbose());
  addCommand(new Round::Console::use());
  addCommand(new Round::Console::rpm());
  
  // alias commands
  addCommand(new Round::Console::exit());
  addCommand(new Round::Console::question());
  
  // RPC method
  addCommand(new Round::Console::method());
}

void Round::Console::Client::initOptions() {
  addOption(new Option('r', "<ipaddr:port>", "Update cluster on given host"));
  addOption(new Option('h', "", "Prints this help message"));
}
void Round::Console::Client::setFirstArgument(const std::string &argValue)
{
  Program::setFirstArgument(argValue);
  
  this->promptName = this->programName;
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

const char *Round::Console::Client::getPromptName()
{
  return promptName.c_str();
}

bool Round::Console::Client::isConsoleCommand(const Input &input) {
  return this->commands.hasCommand(&input);
}

bool Round::Console::Client::isRPCCommand(const Input &input) {
  size_t paramBeginIdx = input.line.find_first_of(method::PARAM_BEGIN);
  if (paramBeginIdx == std::string::npos)
    return false;
  size_t paramEndIdx = input.line.find_first_of(method::PARAM_END);
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

bool Round::Console::Client::isDaemonCommand(const Input &input) {
  return Command::IsDaemon(&input);
}

bool Round::Console::Client::execConsoleCommand(const Input &input, Message *msg, Error *err) {
  return this->commands.execCommand(this, &input, msg, err);
}

bool Round::Console::Client::execRPCCommand(const Input &input, Message *msg, Error *err) {
  Command *cmd = this->commands.getCommand(method::NAME);
  if (!cmd)
    return false;
  return cmd->exec(this, &input, msg, err);
}

void Round::Console::Client::usage() {
  std::cout << "Usage: " << getProgramName() << " [-options] <command>" << std::endl;
  std::cout << std::endl;
  
  printOptions();
  
  Command *help = this->commands.getCommand(Round::Console::help::NAME);
  if (help) {
    std::cout << std::endl;
    help->exec(this, NULL, NULL, NULL);
  }
}
