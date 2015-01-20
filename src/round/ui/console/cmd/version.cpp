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

const std::string Round::Console::version::NAME = "version";

const std::string Round::Console::version::getDescription() const {
  return "Show version number";
}

bool Round::Console::version::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  std::cout << ROUNDCC_PRODUCT_VERSION << std::endl;
  return true;
}
