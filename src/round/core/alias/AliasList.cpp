/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Alias.h>

Round::AliasList::AliasList() {
}

Round::AliasList::~AliasList() {
}

bool Round::AliasList::addAlias(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  if (getAliasByName(name))
    return false;
  
  Alias *alias = new Alias();
  if (!alias)
    return false;
  
  alias->setName(name);
  
  if (!alias->isValid()) {
    delete alias;
    return false;
  }
  
  lock();
  
  bool isSuccess = add(alias);

  unlock();

  return isSuccess;
}

bool Round::AliasList::setAlias(const std::string &name, const std::string &srcObj, const std::string &destObj) {
  Alias *alias = getAliasByName(name);
  if (alias) {
    lock();
    remove(alias);
    unlock();
  }
  
  return addAlias(name, srcObj, destObj);
}

Round::Alias *Round::AliasList::getAliasByName(const std::string &name) const {

  lock();
  
  Alias *foundRuote = NULL;
  
  for (AliasList::const_iterator aliasIt = begin(); aliasIt != end(); aliasIt++) {
    Alias *alias = *aliasIt;
    if (alias->isName(name)) {
      foundRuote = alias;
      break;
    }
  }

  unlock();

  return foundRuote;
}
