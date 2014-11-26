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

#include <round/core/NodeMessage.h>

const std::string Round::NodeResponse::KEY_ERROR_CODE = "_error_code";
const std::string Round::NodeResponse::KEY_ERROR_MESSAGE = "_error_message";

Round::NodeResponse::NodeResponse() {
}

Round::NodeResponse::~NodeResponse() {
}
