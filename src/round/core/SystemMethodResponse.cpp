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

#include <round/core/SystemMethod.h>

const std::string Round::SystemMethodResponse::NAME     = "name";
const std::string Round::SystemMethodResponse::IP       = "ip";
const std::string Round::SystemMethodResponse::PORT     = "port";
const std::string Round::SystemMethodResponse::HASH     = "hash";
const std::string Round::SystemMethodResponse::VERSION  = "version";
const std::string Round::SystemMethodResponse::CLUSTER  = "cluster";
const std::string Round::SystemMethodResponse::CLUSTERS = "clusters";

Round::SystemMethodResponse::SystemMethodResponse(NodeResponse *nodeRes) {
  this->nodeRes = nodeRes;
  
  this->nodeRes->setVersion(RPC::JSON::VERSION);
}
