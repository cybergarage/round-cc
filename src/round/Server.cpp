/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/Server.h>
#include <round/core/HTTP.h>

int Round::Server::DEFAULT_HTTPD_PORT = Round::LocalConfig::DEFAULT_HTTPD_PORT;
Round::Logger Round::Server::logger;

Round::Server::Server() {
  if (!uHTTP::Logger::HasSharedInstance()) {
    Logger::SetSharedInstance(&this->logger);
  }
  initialize();
}

Round::Server::~Server() {
  finalize();
}

void Round::Server::setHttpdPort(int port) {
  getNodeConfig()->setHttpdBindPort(port);
}

bool Round::Server::getLogFilename(std::string *value, Round::Error *error) {
  return getNodeConfig()->getLogFilename(value, error);
}

bool Round::Server::getErrorLogFilename(std::string *value, Round::Error *error) {
  return getNodeConfig()->getErrorLogFilename(value, error);
}
