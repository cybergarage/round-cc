/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/RPC.h>

Round::RPC::JSON::Request::Request() {
  set(JSON_RPC, VERSION);
}

Round::RPC::JSON::Request::~Request() {
}

bool Round::RPC::JSON::Request::isValid() {
  if (!hasKey(JSON_RPC))
    return false;

  if (!hasKey(METHOD))
    return false;
  
  int value;
  if (get(METHOD, &value))
    return false;

  return true;
}

bool Round::RPC::JSON::Request::isNotify() {
  if (!isValid())
    return false;
  return !hasKey(ID);
}
