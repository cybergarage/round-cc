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
#include <sstream>

#include <round/core/local/method/SystemMethod.h>

////////////////////////////////////////
// SystemGetRegistryResponse
////////////////////////////////////////

bool Round::SystemGetRegistryResponse::setRegistry(const Registry reg) {
  JSONDictionary *resultDict = nodeRes->getResultDict();
  if (!resultDict)
    return false;
  
  std::string sval;
  time_t tval;
  
  if (reg.getKey(&sval)) {
    resultDict->set(Registry::KEY, sval);
  }

  if (reg.getValue(&sval)) {
    resultDict->set(Registry::VALUE, sval);
  }

  if (reg.getTimestamp(tval)) {
    resultDict->set(Registry::TS, tval);
  }

  if (reg.getLogicalTimestamp(tval)) {
    resultDict->set(Registry::LTS, tval);
  }

  return true;
}

bool Round::SystemGetRegistryResponse::getRegistry(Registry *reg) {
  JSONDictionary *resultDict = nodeRes->getResultDict();
  if (!resultDict)
    return false;
  
  std::string sval;
  time_t tval;

  if (resultDict->get(Registry::KEY, &sval)) {
    reg->setKey(sval);
  }

  if (resultDict->get(Registry::VALUE, &sval)) {
    reg->setValue(sval);
  }

  if (resultDict->get(Registry::TS, &tval)) {
    reg->setTimestamp(tval);
  }
  
  if (resultDict->get(Registry::LTS, &tval)) {
    reg->setLogicalTimestamp(tval);
  }

  return true;
}
