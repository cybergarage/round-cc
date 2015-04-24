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
  std::string sval;
  time_t tval;
  
  if (reg.getKey(&sval)) {
    nodeRes->set(Registry::KEY, sval);
  }

  if (reg.getValue(&sval)) {
    nodeRes->set(Registry::VALUE, sval);
  }

  if (reg.getTimestamp(tval)) {
    nodeRes->set(Registry::TS, tval);
  }

  if (reg.getLogicalTimestamp(tval)) {
    nodeRes->set(Registry::LTS, tval);
  }

  return true;
}

bool Round::SystemGetRegistryResponse::getRegistry(Registry *reg) {
  std::string sval;
  time_t tval;

  if (nodeRes->get(Registry::KEY, &sval)) {
    reg->setKey(sval);
  }

  if (nodeRes->get(Registry::VALUE, &sval)) {
    reg->setValue(sval);
  }

  if (nodeRes->get(Registry::TS, &tval)) {
    reg->setTimestamp(tval);
  }
  
  if (nodeRes->get(Registry::LTS, &tval)) {
    reg->setLogicalTimestamp(tval);
  }

  return true;
}
