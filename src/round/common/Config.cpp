/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <fstream>
#include <strstream>

#include <round/common/Config.h>
#include <round/common/StringTokenizer.h>
#include <round/core/ErrorNo.h>

const std::string Round::Config::PATH_DELIM = "/";
const std::string Round::Config::ERRMSG_FILE_OPEN = "Failed to open configuration file.";
const std::string Round::Config::ERRMSG_PARSER = "Failed to parse configuration.";
const std::string Round::Config::ERRMSG_KEY_NOT_FOUND = "Key is not found";
const std::string Round::Config::ERRMSG_KEY_VALUE_INVALID = "Key type is invalid";

Round::Config::Config() {
  this->rootDict = NULL;
  init();
}

Round::Config::~Config() {
  clear();
}

bool Round::Config::init() {
  clear();
  this->rootDict = new JSONDictionary();
  return true;
}

bool Round::Config::clear() {
  if (this->rootDict) {
    delete this->rootDict;
  }
  this->rootDict = NULL;
  return true;
}

bool Round::Config::loadFromStream(std::istream &in, Error *err) {
  clear();
  
  std::string lineString;
  std::strstream jsonString;
  while (std::getline(in, lineString)) {
    if (lineString.size() <= 0)
      continue;
    if (lineString.find("#") == 0)
      continue;
    jsonString << lineString;
  }

  JSONParser jsonParser;
  if (!jsonParser.parse(jsonString.str(), err)) {
    return false;
  }
      
  JSONObject *jsonObj = jsonParser.popRootObject();
  if (!jsonObj)
    return false;

  this->rootDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (!this->rootDict) {
    delete jsonObj;
    return false;
  }

  return true;
}

bool Round::Config::loadFromString(const std::string &string, Error *err) {
  std::strstream ss;
  ss << string;
  return loadFromStream(ss, err);
}

bool Round::Config::loadFromFile(const std::string &filename, Error *err) {
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in); 
  if (!ifs.is_open()) {
    std::string errMsg = ERRMSG_FILE_OPEN + " (" + filename + ")";
    setErrorMessage(errMsg, err);
    return false;
  }
  
  bool parseResult = loadFromStream(ifs, err);
  ifs.close();
  return parseResult; 
}

bool Round::Config::getObjectByPath(const std::string &pathString, JSONObject **jsonObj, Error *err) const {
  *jsonObj = NULL;
  
  StringTokenizer tokenizer(pathString, PATH_DELIM);
  StringTokenList tokens;

  if (0 < tokenizer.getTokens(&tokens)) {
    JSONDictionary *parentDict = this->rootDict;
    for (StringTokenList::iterator token = tokens.begin(); token != tokens.end(); token++) {
      if (!parentDict) {
        *jsonObj = NULL;
        break;
      }
      if (!parentDict->get(*token, jsonObj)) {
        *jsonObj = NULL;
        break;
      }
      parentDict = dynamic_cast<JSONDictionary *>(*jsonObj);
    }
  }

  if (!jsonObj) {
    std::string errMsg = ERRMSG_KEY_NOT_FOUND + " (" + pathString + ").";
    setErrorMessage(errMsg, err);
    return false;
  }
  
  return true;
}

bool Round::Config::getStringByPath(const std::string &pathString, std::string *value, Error *err) const {
  JSONObject *jsonObj;
  if (!getObjectByPath(pathString, &jsonObj, err))
    return false;
  
  JSONString *jsonString = dynamic_cast<JSONString *>(jsonObj);
  if (!jsonString) {
    std::string errMsg = ERRMSG_KEY_VALUE_INVALID + " (" + pathString + ").";
    setErrorMessage(errMsg, err);
    return false;
  }
  
  if (!jsonString->get(value)) {
    std::string errMsg = ERRMSG_KEY_VALUE_INVALID + " (" + pathString + ").";
    setErrorMessage(errMsg, err);
    return false;
  }

  return true;
}

bool Round::Config::getIntegerByPath(const std::string &pathString, int *value, Error *err) const {
  JSONObject *jsonObj;
  if (!getObjectByPath(pathString, &jsonObj, err))
    return false;
  
  JSONString *jsonString = dynamic_cast<JSONString *>(jsonObj);
  if (!jsonString) {
    std::string errMsg = ERRMSG_KEY_VALUE_INVALID + " (" + pathString + ").";
    setErrorMessage(errMsg, err);
    return false;
  }
  
  if (!jsonString->get(value)) {
    std::string errMsg = ERRMSG_KEY_VALUE_INVALID + " (" + pathString + ").";
    setErrorMessage(errMsg, err);
    return false;
  }
  
  return true;
}

void Round::Config::setErrorMessage(const std::string &message, Error *error) const {
  if (!error)
    return;
  error->setCode(NodeErrorConfigurationFailure);
  error->setMessage(message);
}
