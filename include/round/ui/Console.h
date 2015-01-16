/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CONSOLE_CLIENT_H_
#define _ROUNDCC_CONSOLE_CLIENT_H_

#include <string>
#include <round/Client.h>
#include <round/common/Vector.h>

namespace Round {

namespace Console {

class Option : public std::string {
    
  public:
    
  Option() {}
};
  
  
class Options : Round::Vector<Option> {
    
 public:
    
  Options() {}
};

class Command {
    
 public:
    
    Command();
    ~Command();

 private:
  std::string name;
};

class Commands : Round::Vector<Command> {
    
 public:
    
  Commands();
  ~Commands();
};
  
class Client : public Round::Client
{

public:
        
  Client();
  ~Client();

private:
  
  static const std::string QUIT;
  static const std::string EXIT;
  static const std::string SHOW;
  static const std::string USE;
  static const std::string SEARCH;
  
  static const std::string CLUSTERS;
  static const std::string NODES;
  
public:
  
  void setProgramNameFromArgument(const std::string &argValue);
  const char *getBootMessage(std::string &buffer);
  const char *getProgramName();
  const char *getPromptName();

  bool isConsoleCommand(const std::string &inputLine) {
    if (isQuitCommand(inputLine))
      return true;
    if (isShowCommand(inputLine))
      return true;
    if (isUseCommand(inputLine))
      return true;
    return false;
  }
  
  bool isQuitCommand(const std::string &inputLine);
  
  bool isQueryCommand(const std::string &inputLine);

  bool isUnknownCommand(const std::string &inputLine) {
    if (isConsoleCommand(inputLine))
      return false;
    if (isQueryCommand(inputLine))
      return false;
    return true;
  }

  bool show(const std::vector<std::string> &commands, Error *error);
  bool use(const std::vector<std::string> &commands, Error *error);
  
  bool exec(const std::string &command, Error *error);

private:
  
  bool isShowCommand(const std::string &inputLine) {
    return isCommand(SHOW, inputLine);
  }
  
  bool isUseCommand(const std::string &inputLine) {
    return isCommand(USE, inputLine);
  }
  
  bool isSearchCommand(const std::string &inputLine) {
    return isCommand(SEARCH, inputLine);
  }
  
private:
  
  bool isCommand(const std::string &command, const std::string &inputLine);
  
private:

  std::string programtName;
  std::string promptName;
};

}

}

#endif
