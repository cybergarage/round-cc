/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/core/Logger.h>

bool Round::Logger::HasSharedInstance() {
  return uHTTP::Logger::HasSharedInstance();
}

Round::Logger *Round::Logger::GetSharedInstance() {
  return (Round::Logger *)uHTTP::Logger::GetSharedInstance();
}

Round::Logger::Logger() {
  setLevel(uHTTP::LoggerTarget::INFO);
}

Round::Logger::~Logger() {
}
