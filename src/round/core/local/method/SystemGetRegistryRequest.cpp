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
// SystemGetRegistryRequest
////////////////////////////////////////

void Round::SystemGetRegistryRequest::setKey(const std::string &value) {
  JSONDictionary paramDict;
  paramDict.set(Registry::KEY, value);

  std::string paramsStr;
  paramDict.toJSONString(&paramsStr);
  setParams(paramsStr);
}
