/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
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

typedef const std::string Param;

class Params : public std::vector<Param> {
 public:
  Params() {}
  
  void addParam(Param &param) {
    push_back(param);
  }
};

class Input{
public:
  std::string cmd;
  Params params;
  
public:
  Input();
  Input(const std::string &inputLine);
  bool parse(const std::string &inputLine);

private:
  void clear();
};

typedef std::string Message;
  
class Command {
 public:
  
  static const std::string QUIT;
  static const std::string EXIT;
  static const std::string SHELL;
  
 public:
  std::string name;
  
 public:
    
  Command(const std::string &name);
  ~Command();

  const std::string &getName() const {
    return this->name;
  }
  
  static bool IsCommand(const std::string &name, const Input *input);
  static bool IsQuit(const Input *input);
  static bool IsShell(const Input *input);
  
  bool isCommand(const Input *input);
  
  virtual bool exec(Round::Client *client, const Params *params, Message *msg, Error *err) const = 0;
};

class Commands : std::map<std::string, Command*> {
    
 public:
    
  Commands();
  ~Commands();
  
  bool addCommand(Command *cmd);
  bool hasCommand(const Input *input) const ;
  bool execCommand(Round::Client *client, const Input *input, Message *msg, Error *err) const ;
  
private:
  void init();
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

  bool isQuitCommand(const Input &input);
  bool isShellCommand(const Input &input);
  
  bool isConsoleCommand(const Input &input);
  
  bool execConsoleCommand(const Input &input, Message *msg, Error *err);
  
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
