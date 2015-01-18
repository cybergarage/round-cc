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

class list : public Command {
public:
  static const std::string NAME;
  list() : Command(NAME) {}
  virtual bool exec(Round::Client *client, const Params *params, Message *msg, Error *err) const;
};

}

}

#endif
