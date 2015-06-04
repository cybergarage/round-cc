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

const std::string Round::set_alias::NAME = ROUNDCC_SYSTEM_METHOD_SET_ALIAS;
const std::string Round::set_alias::ALIAS_NAME = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::set_alias::ALIAS_METHOD = ROUNDCC_SYSTEM_METHOD_PARAM_METHOD;
const std::string Round::set_alias::ALIAS_DEFAULTS = ROUNDCC_SYSTEM_METHOD_PARAM_DEFAULTS;

static const std::string ALIAS_NAME;
static const std::string ALIAS_METHOD;
static const std::string ALIAS_DEFAULTS;

Round::set_alias::set_alias() : system_method(NAME) {
}

Round::set_alias::~set_alias() {
}

bool Round::set_alias::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
  
  std::string name, method;
  
  if (!paramDict->get(ALIAS_NAME, &name))
    return false;
  
  if (!paramDict->get(ALIAS_METHOD, &method))
    return false;
  
  if ((name.length() <= 0) || (method.length() <= 0))
    return false;

  // Optional Parameters
  
  std::string defaults;
  paramDict->get(ALIAS_DEFAULTS, &defaults);

  // Set alias
  
  Alias *alias = new Alias();
  
  alias->setName(name);
  alias->setObject(method);
  alias->setDefaults(defaults);
  
  return node->setAlias(alias);
}
