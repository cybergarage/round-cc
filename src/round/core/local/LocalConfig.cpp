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
#include <round/core/LocalNode.h>
#include <round/common/Error.h>
#include <round/common/Random.h>

#include <uhttp/net/HostInterface.h>

const std::string Round::LocalConfig::BIND_ADDR = "bind_addr";
const std::string Round::LocalConfig::BIND_PORT = "bind_port";
const std::string Round::LocalConfig::CLUSTER = "cluster";
const std::string Round::LocalConfig::LOG_FILE = "log_file";

const std::string Round::LocalConfig::AUTO = "auto";
const std::string Round::LocalConfig::DEFALUT_CLUSTER = ROUNDCC_PRODUCT_NAME;
int Round::LocalConfig::BIND_PORT_RANGE_MIN = 4004;
int Round::LocalConfig::BIND_PORT_RANGE_MAX = 9999;

Round::LocalConfig::LocalConfig() {
}

Round::LocalConfig::~LocalConfig() {
}

bool Round::LocalConfig::isValid(Error *error) {
  return true;
}

////////////////////////////////////////
// Getter
////////////////////////////////////////

bool Round::LocalConfig::getBindAddress(std::string *value, Error *error) const {
  if (getStringByPath(BIND_ADDR, value, error) == false)
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

bool Round::LocalConfig::getBindPort(int *value, Error *error) const {
  if (!getIntegerByPath(BIND_PORT, value, error)) {
    Random randomPort(BIND_PORT_RANGE_MIN, BIND_PORT_RANGE_MAX);
    *value = randomPort.rand();
  }
  return true;
}

bool Round::LocalConfig::getCluster(std::string *value, Error *error) const {
  if (!getStringByPath(CLUSTER, value, error)) {
    *value = DEFALUT_CLUSTER;
  }
  return true;
}

bool Round::LocalConfig::getLogFilename(std::string *value, Error *error) const {
  return getStringByPath(LOG_FILE, value, error);
}

////////////////////////////////////////
// Setter
////////////////////////////////////////

bool Round::LocalConfig::setBindAddress(const std::string &value, Error *error) {
  return setStringByPath(BIND_ADDR, value, error);
}

bool Round::LocalConfig::setBindPort(int value, Error *error) {
  return setIntegerByPath(BIND_PORT, value, error);
}

bool Round::LocalConfig::setCluster(const std::string &value, Error *error) {
  return setStringByPath(CLUSTER, value, error);
}

bool Round::LocalConfig::setLogFilename(const std::string &value, Error *error) {
  return setStringByPath(LOG_FILE, value, error);
}
