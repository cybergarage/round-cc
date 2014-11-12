/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_PROPERTIES_H_
#define _FRACTALCC_PROPERTIES_H_

#include <round/common/Dictionary.h>

namespace Round {
  
class Properties : public Dictionary {
 public:
  Properties();
  ~Properties();

  void setProperty(const std::string &key, const std::string &value);
  bool hasProperty(const std::string &key);
  const char *getProperty(const std::string &key, std::string *value, const std::string &defaultValue = "");
};

}

#endif
