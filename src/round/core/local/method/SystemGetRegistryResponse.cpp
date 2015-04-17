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
    nodeRes->set(get_reg::KEY, sval);
  }

  if (reg.getValue(&sval)) {
    nodeRes->set(get_reg::VALUE, sval);
  }

  if (reg.getTimestamp(tval)) {
    nodeRes->set(get_reg::TS, tval);
  }

  if (reg.getLogicalTimestamp(tval)) {
    nodeRes->set(get_reg::LTS, tval);
  }

  return true;
}

bool Round::SystemGetRegistryResponse::getRegistry(Registry *reg) {
  std::string sval;
  time_t tval;

  if (nodeRes->get(get_reg::KEY, &sval)) {
    reg->setKey(sval);
  }

  if (nodeRes->get(get_reg::VALUE, &sval)) {
    reg->setValue(sval);
  }

  if (nodeRes->get(get_reg::TS, &tval)) {
    reg->setTimestamp(tval);
  }
  
  if (nodeRes->get(get_reg::LTS, &tval)) {
    reg->setLogicalTimestamp(tval);
  }

  return true;
}
