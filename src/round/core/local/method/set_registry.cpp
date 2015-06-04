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

const std::string Round::set_registry::NAME = ROUNDCC_SYSTEM_METHOD_SET_REGISTRY;

Round::set_registry::set_registry() : system_method(NAME) {
}

Round::set_registry::~set_registry() {
}

bool Round::set_registry::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
  if (!paramDict->get(Registry::KEY, &key))
    return false;
  
  std::string value;
  if (!paramDict->get(Registry::VALUE, &value))
    return false;
  
  return node->setRegistry(key, value);
}
