/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>

#include <round/core/NodeConfig.h>
#include <round/common/Error.h>

static const std::string FRACTAL_CONFIG_ERRMSG_OPEN = "Failed to open configuration file.";
static const std::string FRACTAL_CONFIG_ERRMSG_PARSER = "Failed to parse configuration.";
static const std::string FRACTAL_CONFIG_ERRMSG_MISSING = "Bad or missing configuration.";

Round::NodeConfig::NodeConfig() {
}

Round::NodeConfig::~NodeConfig() {
  clear();
}

bool Round::NodeConfig::loadFromStream(std::istream &in, Error *error) {
if (Configuration::loadFromStream(in) == false) {
    setErrorMessage(FRACTAL_CONFIG_ERRMSG_PARSER, error);
    return false;
  }
  return isValid(error);
}

bool Round::NodeConfig::loadFromString(const std::string &string, Error *error) {
  std::stringstream ss;
  ss << string;
  return loadFromStream(ss, error);
}

bool Round::NodeConfig::loadFromFile(const std::string &filename, Error *error) {
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in); 
  if (!ifs.is_open()) {
    std::string errMsg = FRACTAL_CONFIG_ERRMSG_OPEN + " (" + filename + ")";
    setErrorMessage(errMsg, error);
    return false;
  }
  bool parseResult = loadFromStream(ifs, error);
  ifs.close();

  if (!parseResult) {
    std::string errMsg = " (" + filename + ")";
    addErrorMessage(errMsg, error);
  }

  return parseResult; 
}

bool Round::NodeConfig::isValid(Error *error) {
  for (int i = 0; i<getSectionCount(); i++) {
    size_t sectionKeyCount = getSectionKeyCount(i);
    for (size_t j = 0; j<sectionKeyCount; j++) {
      if (hasValue(i, j))
        continue;
      setErrorMessage(FRACTAL_CONFIG_ERRMSG_MISSING, error);
      std::string sectionString = getSectionString(i);
      std::string keyString = getSectionKeyString(i, j);
      std::string errMsg = " (" + sectionString + ":" +  keyString + ")";
      addErrorMessage(errMsg, error);
      return false;
    }
  }
  return true;
}

bool Round::NodeConfig::hasValue(size_t section, size_t key) const {
  std::string value;
  Round::Error error;
  if (getValue(section, key, &value, &error) == false)
    return false;
  return (0 < value.length()) ? true : false;
}

bool Round::NodeConfig::getValue(size_t section, size_t key, std::string *value, Error *error) const {
  std::string sectionString = getSectionString(section);
  std::string keyString = getSectionKeyString(section, key);

  if (getString(sectionString, keyString, value) == true)
    return true;

  setErrorMessage(FRACTAL_CONFIG_ERRMSG_MISSING, error);
  std::string errMsg = " (" + sectionString + ":" +  keyString + ")";
  addErrorMessage(errMsg, error);

  return false;
}

bool Round::NodeConfig::getValue(size_t section, size_t key, int *value, Error *error) const {
  std::string stringValue;
  if (getValue(section, key, &stringValue, error) == false)
    return false;
  *value = atoi(stringValue.c_str());
  return true;
}

bool Round::NodeConfig::setValue(size_t section, size_t key, const std::string &value) {
  std::string sectionString = getSectionString(section);
  std::string keyString = getSectionKeyString(section, key);
  return set(sectionString, keyString, value);
}

bool Round::NodeConfig::setValue(size_t section, size_t key, int intValue) {
  std::ostringstream strValue;
  strValue << intValue;
  return setValue(section, key, strValue.str());
}

void Round::NodeConfig::setErrorMessage(const std::string &message, Error *error) const {
  if (!error)
    return;
  error->setCode(NodeErrorConfigurationFailure);
  error->setMessage(message);
}

void Round::NodeConfig::addErrorMessage(const std::string &message, Error *error) const {
  if (!error)
    return;
  std::string errMesssage = error->getMessage();
  errMesssage.append(message);
  error->setMessage(errMesssage);
}

ssize_t Round::NodeConfig::getSectionIndex(const std::string &value) const {
  for (int n = 0; n < getSectionCount(); n++) {
    std::string sectionString = getSectionString(n);
    if (sectionString.compare(value) == 0)
      return n;
  }

  return -1;
}

ssize_t Round::NodeConfig::getSectionKeyIndex(size_t section, const std::string &value) const {
  size_t sectionKeyCount = getSectionKeyCount(section);
  for (size_t n = 0; n < sectionKeyCount; n++) {
    std::string keyString = getSectionKeyString(section, n);
    if (keyString.compare(value) == 0)
      return n;
  }
  return -1;
}
