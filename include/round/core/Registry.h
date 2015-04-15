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

#include <time.h>
#include <string>
#include <map>

namespace Round {

class Registry {
  
public:
  Registry();
  virtual ~Registry();

  bool setKey(const std::string &value);
  bool getKey(std::string *value) const;
  const std::string getKey() const;
  
  bool setValue(const std::string &value);
  bool getValue(std::string *value) const;
  const std::string getValue() const;
  
  bool setTimestamp(const time_t value);
  bool getTimestamp(time_t &value) const;
  time_t getTimestamp() const;

  bool setLogicalTimestamp(const time_t value);
  bool getLogicalTimestamp(time_t &value) const;
  time_t getLogicalTimestamp() const;
  
  bool equals(const Registry &reg) const;
  bool equals(const Registry *reg) const;
  bool equalsWithTimestamp(const Registry &reg) const;
  bool equalsWithTimestamp(const Registry *reg) const;
  
private:
  
  std::string key;
  std::string value;
  time_t      ts;
  time_t      lts;
};

class RegistryMap : public std::map<std::string, Registry> {
    
 public:
  
  RegistryMap();
  ~RegistryMap();

  bool set(const Registry reg);
  bool get(const std::string &key, Registry *reg) const;

  bool set(const std::string &key, const std::string &value);
  bool get(const std::string &key, std::string *value) const;
};

class RegistryManager : public RegistryMap {
    
 public:
  
  RegistryManager();
  virtual ~RegistryManager();
};

}

#endif
