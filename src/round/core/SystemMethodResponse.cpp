/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/LocalNode.h>

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;
  
  this->nodeRes->setVersion(RPC::JSON::VERSION);
}
