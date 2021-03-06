/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CONSOLE_H_
#define _ROUNDCC_CONSOLE_H_

#include <map>
#include <string>

#include <round/Client.h>
#include <round/Server.h>
#include <round/common/Vector.h>

namespace Round {

namespace Console {

////////////////////////////////////////
// Program
////////////////////////////////////////

class Option {
 public:
  char type;
  std::string option;
  std::string description;
  
 public:
    
  Option(char c, const std::string &opt, const std::string &desc) {
    this->type = c;
    this->option = opt;
    this->description = desc;
  }
  
  virtual ~Option() {}
  
  const char getId() const {
    return this->type;
  }

  const std::string &getOption() {
    return this->option;
  }
  
  const std::string &getDescription() {
    return this->description;
  }
};
  
class Options : public std::map<char, Option*> {
 public:
    
  Options();
  ~Options();

  bool addOption(Option *opt);
  
private:
  void init();
  void clear();
};

class Program
{
public:
    
  Options options;
    
public:
    
  Program();
  ~Program();
    
  void setFirstArgument(const std::string &argValue);
  const char *getProgramName();
  
  void init();
  void initOptions();
    
  bool addOption(Option *opt) {
    return this->options.addOption(opt);
  }

  void printOptions();
  
protected:
    
  std::string programName;
};

////////////////////////////////////////
// Client
////////////////////////////////////////
  
typedef const std::string Param;

class Params : public std::vector<std::string> {
 public:
  Params() {}
  
  void addParam(Param &param) {
    push_back(param);
  }
};

class Input{
public:
  std::string line;
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
class Client;
  
class Command {
 public:
  
  static const std::string TAB;
  
  static const std::string QUIT;
  static const std::string EXIT;
  static const std::string SHELL;
  static const std::string DONE;
  static const std::string DAEMON;
  
 public:
  std::string name;
  
 public:
    
  Command(const std::string &name);
  virtual ~Command();

  const std::string getName() const {
    return this->name;
  }
  
  static bool IsCommand(const std::string &name, const Input *input);
  static bool IsQuit(const Input *input);
  static bool IsShell(const Input *input);
  static bool IsDaemon(const Input *input);
  
  bool isCommand(const Input *input);
  
  virtual bool exec(Client *client, const Input *input, Message *msg, Error *err) const = 0;
  virtual const std::string getDescription() const = 0;
  virtual const std::string getOptionDescription() const {return "";};
  
  void sleep(int msec) const ;
  void waitAnimation(int msec, const std::string &desc = "", const std::string &done = ROUNDCC_MESSAGE_DONE) const ;
};

class Commands : public std::map<std::string, Command*> {
    
 public:
    
  Commands();
  ~Commands();
  
  bool addCommand(Command *cmd);
  bool hasCommand(const Input *input) const ;
  Command *getCommand(const std::string &name) const ;
  bool execCommand(Client *client, const Input *input, Message *msg, Error *err) const ;
  
private:
  void init();
  void clear();

  bool isNonExecutedCommand(const Input *input) const;
};
  
class Client : public Round::Client, public Program
{
public:
  
  Commands commands;

public:
        
  Client();
  ~Client();
  
  void setFirstArgument(const std::string &argValue);
  const char *getBootMessage(std::string &buffer);
  const char *getPromptName();

  bool addCommand(Command *cmd) {
    return this->commands.addCommand(cmd);
  }
  
  bool isQuitCommand(const Input &input);
  bool isShellCommand(const Input &input);
  bool isConsoleCommand(const Input &input);
  bool isDaemonCommand(const Input &input);
  bool isRPCCommand(const Input &input);
  
  bool execConsoleCommand(const Input &input, Message *msg, Error *err);
  bool execRPCCommand(const Input &input, Message *msg, Error *err);
  
  void init();
  void initCommands();
  void initOptions();
  void usage();
    
private:

  std::string promptName;
};

////////////////////////////////////////
// Server
////////////////////////////////////////
  
class Server : public Round::Server, public Program
{
public:
    
  Server();
  ~Server();
    
  void initOptions();
  void usage();
};
  
}

}

#endif
