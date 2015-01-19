/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/core/Log.h>
#include <round/ui/console/Command.h>

const std::string Round::Console::verbose::NAME = "verbose";
const std::string Round::Console::verbose::ON = "on";
const std::string Round::Console::verbose::OFF = "off";

bool Round::Console::verbose::exec(Round::Console::Client *client, const Params *params, Message *msg, Error *err) const {
  if (params->size() <= 0) {
    err->setMessage("verbose mode is node specified");
    return false;
  }
  
  Logger *sharedLogger = Logger::GetSharedInstance();
  sharedLogger->clearAllTargets();
  
  const std::string mode = params->at(0);
  if (mode.compare(ON)) {
    int loggerLevel = LoggerLevel::TRACE;
    sharedLogger->setLevel(loggerLevel);
    sharedLogger->addTarget(new LoggerStdoutTarget());
  }
  
  return true;
}

const std::string Round::Console::verbose::getDescription() const {
  return "Set the operation logging level";
}
