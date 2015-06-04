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

const std::string Round::remove_alias::NAME = ROUNDCC_SYSTEM_METHOD_REMOVE_ALIAS;
const std::string Round::remove_alias::ALIAS_NAME = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;

Round::remove_alias::remove_alias() : system_method(NAME) {
}

Round::remove_alias::~remove_alias() {
}

bool Round::remove_alias::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
  
  // Essential Parameters
  
  std::string name;
  
  if (!paramDict->get(ALIAS_NAME, &name))
    return false;
  
  if ((name.length() <= 0))
    return false;
  
  // Remove alias
  
  return node->removeAliasByName(name);
}
