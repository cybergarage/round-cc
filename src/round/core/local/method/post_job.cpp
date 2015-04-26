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

const std::string Round::post_job::NAME   = ROUNDCC_SYSTEM_METHOD_POST_JOB;
const std::string Round::post_job::JOB_LANGUAGE      = ROUNDCC_SYSTEM_METHOD_PARAM_LANGUAGE;
const std::string Round::post_job::JOB_CODE          = ROUNDCC_SYSTEM_METHOD_PARAM_CODE;
const std::string Round::post_job::JOB_ENCODE        = ROUNDCC_SYSTEM_METHOD_PARAM_ENCODE;
const std::string Round::post_job::JOB_ENCODE_BASE64 = ROUNDCC_SYSTEM_METHOD_PARAM_BASE64;


Round::post_job::post_job() : system_method(NAME) {
}

Round::post_job::~post_job() {
}

bool Round::post_job::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
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
  
  std::string scriptLang;
  if (!jsonDict->get(JOB_LANGUAGE, &scriptLang) || (scriptLang.length() <= 0))
    return false;
  
  // This method is removed if the code parameter is null.
  std::string scriptCode;
  jsonDict->get(JOB_CODE, &scriptCode);
  
  // Encode
  int encodeType = Script::ENCODING_NONE;
  std::string encodeTypeStr;
  if (jsonDict->get(JOB_ENCODE, &encodeTypeStr)) {
    if (encodeTypeStr.compare(JOB_ENCODE_BASE64)) {
      encodeType = Script::ENCODING_BASE64;
    }
  }
  
  return node->execJob(scriptLang, scriptCode, encodeType, &err);
}
