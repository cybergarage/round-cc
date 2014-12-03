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

Round::RPC::JSON::Response::Response() {
  set(JSON_RPC, VERSION);
}

Round::RPC::JSON::Response::~Response() {
}

bool Round::RPC::JSON::Response::isValid() {
  if (!hasKey(JSON_RPC))
    return false;
  if (hasKey(ERROR))
    return false;
  if (!hasKey(RESULT))
    return true;
  return false;
}
