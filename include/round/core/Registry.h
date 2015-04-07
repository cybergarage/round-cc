/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_REGISTRY_H_
#define _ROUNDCC_REGISTRY_H_

#include <string>
#include <map>

namespace Round {

class Registry {
  
public:
  Registry();
  virtual ~Registry();

  bool setKey(const std::string &value);
  bool getKey(std::string *value) const;
  
private:
  
  std::string  key;
  std::string  value;
};

class RegistryMap : public std::map<std::string, std::string> {
    
 public:
  
  RegistryMap();
  ~RegistryMap();
};

class RegistryManager : public RegistryMap {
    
 public:
  
  RegistryManager();
  virtual ~RegistryManager();
};

}

#endif
