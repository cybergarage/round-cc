/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_COFIGURATION_H_
#define _ROUNDCC_COFIGURATION_H_

#include <iostream>
#include <round/common/Error.h>

namespace Round {

class JSONObject;
class JSONDictionary;

class Config {
 public:
  static const std::string PATH_DELIM;
  static const std::string ERRMSG_FILE_OPEN;
  static const std::string ERRMSG_PARSER;
  static const std::string ERRMSG_KEY_NOT_FOUND;
  static const std::string ERRMSG_KEY_VALUE_INVALID;
  
 public:
  Config();
  ~Config();

  bool loadFromString(const std::string &string, Error *err);
  bool loadFromFile(const std::string &filename, Error *err);

  bool getObjectByPath(const std::string &pathString, JSONObject **jsonObj, Error *err) const;
  bool getStringByPath(const std::string &pathString, std::string *value, Error *err) const;
  bool getIntegerByPath(const std::string &pathString, int *value, Error *err) const;

  bool setStringByPath(const std::string &pathString, const std::string &value, Error *err);
  bool setIntegerByPath(const std::string &pathString, int value, Error *err);
  
protected:

  bool init();
  bool clear();
  
  bool loadFromStream(std::istream &in, Error *err);
  bool addObjectByPath(const std::string &pathString, JSONObject *jsonObj, Error *err);
  void setErrorMessage(const std::string &message, Error *error) const;
  
private:
  JSONDictionary *rootDict;
};

}

#endif
