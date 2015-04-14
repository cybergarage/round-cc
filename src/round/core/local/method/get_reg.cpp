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

const std::string Round::get_reg::NAME   = ROUNDCC_SCRIPT_GET_REG;
const std::string Round::get_reg::KEY    = "key";
const std::string Round::get_reg::VALUE  = "value";
const std::string Round::get_reg::TS     = "ts";
const std::string Round::get_reg::LTS    = "lts";

Round::get_reg::get_reg() : system_method(NAME) {
}

Round::get_reg::~get_reg() {
}

bool Round::get_reg::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string params;
  if (!nodeReq->getParams(&params))
    return false;
  
  JSONParser jsonParser;
  Error error;
  if (!jsonParser.parse(params, &error))
    return false;
  
  JSONDictionary *paramDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  if (!paramDict)
    return false;
  
  std::string key;
  if (!paramDict->get(KEY, &key))
    return false;

  Registry reg;
  std::string value;
  if (!node->getRegistry(key, &reg))
    return false;

  return nodeRes->setResult(value);
}
