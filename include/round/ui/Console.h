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

#include <map>
#include <string>

#include <round/Client.h>
#include <round/common/Vector.h>

namespace Round {

namespace Console {

class Option : public std::string {
 public:
  char type;
  std::string desc;
  
 public:
    
  Option(char c, const std::string &dest) {
    this->type = c;
    this->desc = desc;
  }
  
  const char getId() const {
    return this->type;
  }

  const std::string &getDescription() const {
    return this->desc;
  }
};
  
class Options : Round::Vector<Option> {
 public:
    
  Options() {}
};

typedef std::string Param;

class Params : std::vector<Param> {
 public:
  Params() {}
};

typedef std::string Message;
  
class Command {
 public:
  
  static const std::string QUIT;
  static const std::string EXIT;
  static const std::string LIST;
  static const std::string USE;
  static const std::string CLUSTERS;
  static const std::string NODES;
  
  static std::string GetCommand(const std::string &inputLine);
  
 public:
  std::string name;
  
 public:
    
  Command();
  ~Command();

  bool isCommand(const std::string &inputLine);
  
  virtual bool exec(Round::Client *client, const Params *params, Message *msg, Error *err) = 0;
};

class Commands : std::map<std::string, Command*> {
    
 public:
    
  Commands();
  ~Commands();
  
  bool hasCommand(const std::string &inputLine);
  bool execCommand(Round::Client *client, const std::string &inputLine, Message *msg, Error *err); 
};
  
class Client : public Round::Client
{

public:
        
  Client();
  ~Client();

public:
  
  void setProgramNameFromArgument(const std::string &argValue);
  const char *getBootMessage(std::string &buffer);
  const char *getProgramName();
  const char *getPromptName();

  bool isConsoleCommand(const std::string &inputLine);
  bool isConsoleQuitCommand(const std::string &inputLine);
  bool execConsoleCommand(const std::string &inputLine, Message *msg, Error *err);
  
private:

  void init();
  void initOptions();
  void initCommands();
  
private:

  std::string programtName;
  std::string promptName;

  Options options;
  Commands commands;
};

}

}

#endif
