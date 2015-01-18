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

const std::string Round::set_method::NAME   = "set_method";
const std::string Round::set_method::METHOD_LANGUAGE      = "language";
const std::string Round::set_method::METHOD_NAME          = "name";
const std::string Round::set_method::METHOD_CODE          = "code";
const std::string Round::set_method::METHOD_ENCODE        = "encode";
const std::string Round::set_method::METHOD_ENCODE_BASE64 = "base64";


Round::set_method::set_method() : SystemMethod(NAME) {
}

Round::set_method::~set_method() {
}

bool Round::set_method::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
  
  // Couldn't override 'set_method'
  if (node->isStaticMethod(scriptMethod))
    return false;
  
  std::string scriptLang;
  if (!jsonDict->get(METHOD_LANGUAGE, &scriptLang) || (scriptLang.length() <= 0))
    return false;
  
  // This method is removed if the code parameter is null.
  std::string scriptCode;
  jsonDict->get(METHOD_CODE, &scriptCode);
  
  // Encode
  int encodeType = Script::ENCODING_NONE;
  std::string encodeTypeStr;
  if (jsonDict->get(METHOD_ENCODE, &encodeTypeStr)) {
    if (encodeTypeStr.compare(METHOD_ENCODE_BASE64)) {
      encodeType = Script::ENCODING_BASE64;
    }
  }
  
  return node->setScript(scriptMethod, scriptLang, scriptCode, encodeType, &err);
}
