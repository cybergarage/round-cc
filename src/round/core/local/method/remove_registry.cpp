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

const std::string Round::remove_registry::NAME = ROUNDCC_SYSTEM_METHOD_REMOVE_REGISTRY;

Round::remove_registry::remove_registry() : system_method(NAME) {
}

Round::remove_registry::~remove_registry() {
}

bool Round::remove_registry::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
