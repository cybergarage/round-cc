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

void Round::SystemGetRegistryResponse::setRegistry(const Registry reg) {
  std::string key;
  if (reg.getKey(&key)) {
    nodeRes->set(get_reg::KEY, key);
  }

  std::string value;
  if (reg.getValue(&value)) {
    nodeRes->set(get_reg::VALUE, value);
  }
}
