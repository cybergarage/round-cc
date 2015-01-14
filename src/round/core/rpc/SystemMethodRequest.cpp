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
#include <round/core/LocalNode.h>

const std::string Round::SystemMethodRequest::PREFIX      = "_";

const std::string Round::SystemMethodRequest::LANGUAGE      = "language";
const std::string Round::SystemMethodRequest::NAME          = "name";
const std::string Round::SystemMethodRequest::CODE          = "code";
const std::string Round::SystemMethodRequest::ENCODE        = "encode";
const std::string Round::SystemMethodRequest::ENCODE_BASE64 = "base64";

const std::string Round::SystemMethodRequest::ECHO              = "_echo";
const std::string Round::SystemMethodRequest::SET_METHOD        = "_set_method";
const std::string Round::SystemMethodRequest::GET_NODE_INFO     = "_get_node_info";
const std::string Round::SystemMethodRequest::GET_CLUSTER_INFO  = "_get_cluster_info";
const std::string Round::SystemMethodRequest::GET_NETWORK_INFO  = "_get_network_info";

Round::SystemMethodRequest::SystemMethodRequest() {
  setVersion(RPC::JSON::VER);
}
