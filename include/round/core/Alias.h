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
  
private:
  
  std::string  name;
};

class AliasList : public Vector<Alias> {
    
 public:
  
  AliasList();
  ~AliasList();
  
  bool addAlias(const std::string &name, const std::string &srcObject, const std::string &destObject);
  bool setAlias(const std::string &name, const std::string &srcObject, const std::string &destObject);

  Alias *getAliasByName(const std::string &name) const ;
};

class AliasEngine : public AliasList {
    
public:
    
  AliasEngine();
  virtual ~AliasEngine();
};

class AliasManager : public AliasEngine {
    
 public:
  
  AliasManager();
  virtual ~AliasManager();
};

}

#endif
