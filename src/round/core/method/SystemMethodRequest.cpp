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
#include <round/core/method/SystemMethod.h>

const std::string Round::SystemMethodRequest::PREFIX      = "_";

const std::string Round::SystemMethodRequest::LANGUAGE      = "language";
const std::string Round::SystemMethodRequest::NAME          = "name";
const std::string Round::SystemMethodRequest::CODE          = "code";
const std::string Round::SystemMethodRequest::ENCODE        = "encode";
const std::string Round::SystemMethodRequest::ENCODE_BASE64 = "base64";

const std::string Round::SystemMethodRequest::ECHO              = "_echo";
const std::string Round::SystemMethodRequest::SET_METHOD        = "_set_method";

Round::SystemMethodRequest::SystemMethodRequest() {
  setVersion(RPC::JSON::VER);
}
