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

const std::string Round::Console::verbose::getDescription() const {
  return "Set the operation logging level";
}

const std::string Round::Console::verbose::getOptionDescription() const {
  return "<on|off>";
}

bool Round::Console::verbose::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  if (input->params.size() <= 0) {
    err->setMessage("verbose mode is not specified");
    return false;
  }
  
  Logger *sharedLogger = Logger::GetSharedInstance();
  sharedLogger->clearAllTargets();
  
  const std::string mode = input->params.at(0);
  if (mode.compare(ON)) {
    int loggerLevel = LoggerLevel::TRACE;
    sharedLogger->setLevel(loggerLevel);
    sharedLogger->addTarget(new LoggerStdoutTarget());
  }
  
  return true;
}
