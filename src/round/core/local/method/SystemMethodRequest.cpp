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

#include <round/core/LocalNode.h>
#include <round/core/local/method/SystemMethod.h>

Round::SystemMethodRequest::SystemMethodRequest() {
  setVersion(RPC::JSON::VER);
}
