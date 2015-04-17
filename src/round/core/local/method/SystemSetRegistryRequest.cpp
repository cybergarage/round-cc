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

void Round::SystemSetRegistryRequest::set(const Registry reg) {
  std::string sval;
  
  if (reg.getKey(&sval)) {
    set(get_reg::KEY, sval);
  }

  if (reg.getValue(&sval)) {
    set(get_reg::VALUE, sval);
  }
}
