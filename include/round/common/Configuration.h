/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_COFIGURATION_H_
#define _FRACTALCC_COFIGURATION_H_

#include <iostream>

#include <round/common/Dictionary.h>

namespace Round {
  
class Configuration : public std::map<std::string, Dictionary*> {
 public:
  static const std::string PATH_DELIM;

 public:
  Configuration();
  ~Configuration();

  Configuration(const Configuration& config);
  Configuration &operator=(const Configuration &config);

  bool loadFromString(const std::string &string);
  bool loadFromFile(const std::string &filename);

  bool getString(const std::string &section, const std::string &key, std::string *value) const;
  bool getStringByPath(const std::string &pathString, std::string *value) const;

  void clear();

  bool set(const Configuration &config);
  bool set(const std::string &section, const std::string &key, const std::string &value);

protected:

  bool loadFromStream(std::istream &in);

  bool hasSection(const std::string &section) const;
  Dictionary *getSection(const std::string &section) const;
};

}

#endif
