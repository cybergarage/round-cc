/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/Round.h>
#include <round/ui/console/Command.h>

const std::string Round::Console::quit::NAME = "quit";

const std::string Round::Console::quit::getDescription() const {
  return "Quit interactive shell";
}

bool Round::Console::quit::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  ::exit(EXIT_SUCCESS);
}
