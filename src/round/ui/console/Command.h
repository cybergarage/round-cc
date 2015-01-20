/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CONSOLE_COMMAND_H_
#define _ROUNDCC_CONSOLE_COMMAND_H_

#include <round/ui/Console.h>

namespace Round {

namespace Console {

class shell : public Command {
public:
  static const std::string NAME;
  shell() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class version : public Command {
public:
  static const std::string NAME;
  version() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class list : public Command {
public:
  static const std::string NAME;
  list() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class search : public Command {
public:
  static const std::string NAME;
  search() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class update : public Command {
public:
  static const std::string NAME;
  update() : Command(NAME) {}
  virtual bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};
  
class help : public Command {
public:
  static const std::string NAME;
  help() : Command(NAME) {}
  help(const std::string &name) : Command(name) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class quit : public Command {
public:
  static const std::string NAME;
  quit() : Command(NAME) {}
  quit(const std::string &name) : Command(name) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
};

class verbose : public Command {
public:
  static const std::string NAME;
  static const std::string ON;
  static const std::string OFF;
  verbose() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
  const std::string getOptionDescription() const;
};

class use : public Command {
public:
  static const std::string NAME;
  static const std::string ERROR_CLUSTER_NOTSPECFIED;
  static const std::string ERROR_CLUSTER_NOTFOUND;
  use() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
  const std::string getOptionDescription() const;
};

////////////////////////////////////////////////////////////
// rpc command
////////////////////////////////////////////////////////////

class method : public Command {
public:
  static const std::string NAME;
  static const std::string PARAM_BEGIN;
  static const std::string PARAM_END;
  static const std::string PARAM_SEP;
  static const std::string OBJECT_SEP;
  static const std::string ERROR_OBJECT_NOTSPECEFIED;
  static const std::string ERROR_CLUSTER_NOTFOUND;
  static const std::string ERROR_NODE_NOTFOUND;
  method() : Command(NAME) {}
  bool exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const;
  const std::string getDescription() const;
  const std::string getOptionDescription() const;
};

////////////////////////////////////////////////////////////
// alias commands
////////////////////////////////////////////////////////////

class exit : public quit {
public:
  static const std::string NAME;
  exit() : quit(NAME) {}
};

class question : public help {
public:
  static const std::string NAME;
  question() : help(NAME) {}
};
  

}

}

#endif
