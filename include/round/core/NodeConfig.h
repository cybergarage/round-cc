/******************************************************************
*
* Fractal for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODECOMFIG_H_
#define _ROUNDCC_NODECOMFIG_H_

#include <round/common/Error.h>
#include <round/common/Configuration.h>

namespace Round {
class NodeConfig : public Configuration {
 public:
  NodeConfig();
  ~NodeConfig();
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

  bool loadFromString(const std::string &string, Error *error);
  bool loadFromFile(const std::string &filename, Error *error);

  virtual bool isValid(Error *error);

  bool hasValue(size_t section, size_t key) const;
  bool getValue(size_t section, size_t key, std::string *value, Error *error) const;
  bool getValue(size_t section, size_t key, int *value, Error *error) const;

  bool setValue(size_t section, size_t key, const std::string &value);
  bool setValue(size_t section, size_t key, int value);

  ssize_t getSectionKeyIndex(size_t section, const std::string &value) const;
  ssize_t getSectionIndex(const std::string &value) const;

  size_t getSectionCount() const;
  size_t getSectionKeyCount(size_t section) const;

  const char *getSectionKeyString(size_t section, size_t n) const;
  const char *getSectionString(size_t n) const;

private:

  bool loadFromStream(std::istream &in, Error *error);

  void setErrorMessage(const std::string &message, Error *error) const;
  void addErrorMessage(const std::string &message, Error *error) const;

};

}

#endif
