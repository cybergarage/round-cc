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

Round::AliasMap::AliasMap() {
}

Round::AliasMap::~AliasMap() {
  clear();
}

void Round::AliasMap::clear() {
  for (AliasMap::iterator aliasIt = begin(); aliasIt != end(); aliasIt++) {
    Alias *alias = aliasIt->second;
    if (alias) {
      delete alias;
    }
  }
  std::map<std::string, Alias*>::clear();
}

bool Round::AliasMap::hasAlias(const std::string &name) const {
  return (find(name) != end()) ? true  : false;
}

Round::Alias *Round::AliasMap::findAlias(const std::string &name) const {
  AliasMap::const_iterator valueIt = find(name);
  if (valueIt == end())
    return NULL;
  return valueIt->second;
}

bool Round::AliasMap::getSourceObjects(const std::string &name, std::string *object) const {
  Alias *alias = findAlias(name);
  if (!alias)
    return NULL;
  return alias->getObject(object);
}

bool Round::AliasMap::addAlias(Alias *alias) {
  std::string name;
  if (!alias->getName(&name))
    return false;
  
  if (hasAlias(name))
    return false;
  
  insert(std::pair<std::string, Alias *>(name, alias));

  return true;
}

bool Round::AliasMap::setAlias(Alias *alias) {
  std::string name;
  if (!alias->getName(&name))
    return false;

  if (hasAlias(name)) {
    if (!removeAliasByName(name))
      return false;
  }
  
  return addAlias(alias);
}

bool Round::AliasMap::removeAliasByName(const std::string &name) {
  return (0 < erase(name)) ? true : false;
}
