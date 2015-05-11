/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_ROUTE_H_
#define _ROUNDCC_ROUTE_H_

#include <string>
#include <map>

#include <round/common/Vector.h>

namespace Round {

  
class Alias {
  
public:
  Alias();
  virtual ~Alias();

  bool isValid();
  
  // Name
  
  bool setName(const std::string &value);
  bool getName(std::string *value) const;
  bool isName(const std::string &value) const;
  
  // Source
  
  bool setObject(const std::string &value);
  bool getObject(std::string *value) const;

private:
  
  std::string  name;
  std::string  object;
};

class AliasMap : public std::map<std::string, Alias *> {
  
public:
  
  AliasMap();
  ~AliasMap();
  
  bool hasAlias(const std::string &name) const;
  
  bool addAlias(Alias *alias);
  bool setAlias(Alias *alias);
  bool removeAliasByName(const std::string &name);
  
  void clear();
};

class AliasManager : public AliasMap {
    
 public:
  
  AliasManager();
  virtual ~AliasManager();
};

}

#endif
