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

const std::string Round::remove_method::NAME                 = ROUNDCC_SYSTEM_METHOD_REMOVE_METHOD;
const std::string Round::remove_method::METHOD_NAME          = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;

Round::remove_method::remove_method() : system_method(NAME) {
}

Round::remove_method::~remove_method() {
}

bool Round::remove_method::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string params;
  nodeReq->getParams(&params);

  Error err;
  
  JSONParser jsonParser;
  if (!jsonParser.parse(params, &err))
    return false;
  
  JSONObject *jsonObj = jsonParser.getRootObject();
  if (!jsonObj->isDictionary())
    return false;
  
  JSONDictionary *jsonDict = dynamic_cast<JSONDictionary *>(jsonObj);
  if (!jsonDict)
    return false;
  
  std::string scriptMethod;
  if (!jsonDict->get(METHOD_NAME, &scriptMethod) || (scriptMethod.length() <= 0))
    return false;
  
  // Couldn't remove static methods
  if (node->isStaticMethod(scriptMethod))
    return false;
  
  return node->removeScript(scriptMethod, &err);
}
