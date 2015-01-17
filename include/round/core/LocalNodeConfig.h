/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SERVERNODECOMFIG_H_
#define _ROUNDCC_SERVERNODECOMFIG_H_

#include <round/core/NodeConfig.h>

namespace Round {
class LocalNodeConfig : public NodeConfig {
 public:
  static const std::string DEFAULT_FILENAME;
  static const std::string AUTO;
  static const int DEFAULT_HTTPD_PORT;

  enum Sections {
    General = 0,
    Httpd,
    Log,
    SectionCount,
  };

  enum GeneralSectionKeys {
    Cluster = 0,
    DatabaseDir,
    GeneralKeyCount,
  };

  enum HttpdSectionKeys {
    HttpdBindAddress = 0,
    HttpdBindPort,
    HttpdKeyCount,
  };

  enum LogSectionKeys {
    LogFile = 0,
    ErrorLogFile,
    LogLevel,
    LogKeyCount,
  };

 public:
  LocalNodeConfig();
  ~LocalNodeConfig();

  bool isValid(Error *error);

  size_t getSectionCount() const;
  size_t getSectionKeyCount(size_t section) const;
  
  const char *getSectionKeyString(size_t section, size_t n) const;
  const char *getSectionString(size_t n) const;

 public:
  bool getHttpdBindAddress(std::string *value, Error *error) const;
  bool getHttpdBindPort(int *value, Error *error) const;

  bool getCluster(std::string *value, Error *error) const {
    return getValue(General, Cluster, value, error);
  }
  
  bool getDatabaseDirectory(std::string *value, Error *error) const {
    return getValue(General, DatabaseDir, value, error);
  }

  bool getLogFilename(std::string *value, Error *error) const {
    return getValue(Log, LogFile, value, error);
  }

  bool getErrorLogFilename(std::string *value, Error *error) const {
    return getValue(Log, ErrorLogFile, value, error);
  }

  bool setHttpdBindAddress(const std::string &value) {
    return setValue(Httpd, HttpdBindAddress, value);
  }
  
  bool setHttpdBindPort(int port) {
    return setValue(Httpd, HttpdBindPort, port);
  }
  
  bool setCluster(const std::string &value) {
    return setValue(General, Cluster, value);
  }
  
  bool setDatabaseDirectory(const std::string &value) {
    return setValue(General, DatabaseDir, value);
  }

  bool setLogFilename(const std::string &value) {
    return setValue(Log, LogFile, value);
  }
  
  bool setErrorLogFilename(const std::string &value) {
    return setValue(Log, ErrorLogFile, value);
  }
  
};

}

#endif
