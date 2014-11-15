/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNodeConfig.h>
#include <round/common/Error.h>

#include <uhttp/net/HostInterface.h>

const std::string Round::LocalNodeConfig::DEFAULT_FILENAME = "/etc/round/roundd.ini";
const std::string Round::LocalNodeConfig::AUTO = "auto";
const int Round::LocalNodeConfig::DEFAULT_HTTPD_PORT = 38690;

Round::LocalNodeConfig::LocalNodeConfig() {}

Round::LocalNodeConfig::~LocalNodeConfig() {}

bool Round::LocalNodeConfig::isValid(Error *error) {
  if (NodeConfig::isValid(error) == false)
    return false;
  return true;
}

size_t Round::LocalNodeConfig::getSectionCount() const {
  return SectionCount;
}

size_t Round::LocalNodeConfig::getSectionKeyCount(size_t section) const {
  switch (section) {
    case General:
      return GeneralKeyCount;
    case Httpd:
      return HttpdKeyCount;
  }

  return 0;
}

const char *Round::LocalNodeConfig::getSectionString(size_t type) const  {
  switch (type) {
    case General:
      return "node";
    case Httpd:
      return "httpd";
    case Log:
      return "log";
  }

  return "";
}

const char *Round::LocalNodeConfig::getSectionKeyString(size_t section, size_t key) const {
  switch (section) {
    case General:
      switch (key) {
        case Cluster:
          return "cluster";
        case DatabaseDir:
          return "database_dir";
      }
      break;
    case Httpd:
      switch (key) {
        case HttpdBindAddress:
          return "bind_address";
        case HttpdBindPort:
          return "bind_port";
      }
      break;
    case Log:
      switch (key) {
        case LogFile:
          return "file";
        case ErrorLogFile:
          return "err";
        case LogLevel:
          return "level";
      }
      break;
  }

  return "";
}

bool Round::LocalNodeConfig::getHttpdBindAddress(std::string *value, Error *error) const {
  if (getValue(Httpd, HttpdBindAddress, value, error) == false)
    *value = AUTO;
  if (value->compare(AUTO) == 0) {
    std::string hostInterface = "127.0.0.1";
    if (0 < uHTTP::GetNHostAddresses()) {
      std::string firstInterface;
      uHTTP::GetHostAddress(0, firstInterface);
      hostInterface = firstInterface;
    }
    uHTTP::SetHostInterface(hostInterface);
    *value = hostInterface;
  }
  return true;
}

bool Round::LocalNodeConfig::getHttpdBindPort(int *value, Error *error) const {
  bool hasPort = getValue(Httpd, HttpdBindPort, value, error);
  if (hasPort == false)
    *value = DEFAULT_HTTPD_PORT;
  return hasPort;
}
