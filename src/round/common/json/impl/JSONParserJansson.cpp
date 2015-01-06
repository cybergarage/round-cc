/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <iostream>
#include <sstream>

#include <round/common/JSON.h>
#include <jansson.h>

#if defined(USE_ROUND_JSON_PARSER_JANSSON)

static void RoundToJSONObject(Round::JSONParser *jsonParser, Round::JSONDictionary *parentDict, json_t *jsonTDict);
static void RoundToJSONObject(Round::JSONParser *jsonParser, Round::JSONArray *parentArray, json_t *jsonTArray);

static Round::JSONObject *RoundToJSONObject(Round::JSONParser *jsonParser, json_t *jsonTObj) {
  switch (json_typeof(jsonTObj)) {
  case JSON_OBJECT:
    return jsonParser->createJSONDictionary();
  case JSON_ARRAY:
    return jsonParser->createJSONArray();
  case JSON_NULL:
      return new Round::JSONNull();
  case JSON_STRING:
    {
      Round::JSONString *jsonObj = new Round::JSONString();
      jsonObj->set(json_string_value(jsonTObj));
      return jsonObj;
    }
  case JSON_INTEGER:
    {
      Round::JSONInteger *jsonObj = new Round::JSONInteger();
      jsonObj->set((int)json_integer_value(jsonTObj));
      return jsonObj;
    }
  case JSON_REAL:
    {
      Round::JSONReal *jsonObj = new Round::JSONReal();
      jsonObj->set(json_real_value(jsonTObj));
      return jsonObj;
    }
  case JSON_TRUE:
  case JSON_FALSE:
    {
      Round::JSONBoolean *jsonObj = new Round::JSONBoolean();
      jsonObj->set((int)json_integer_value(jsonTObj));
      return jsonObj;
    }
  }
  return new Round::JSONNull();
}

static void RoundToJSONObject(Round::JSONParser *jsonParser, Round::JSONDictionary *parentDict, json_t *jsonTDict) {
  if (!jsonParser || !parentDict)
    return;

  const char *jsonKey;
  json_t *jsonTObj;
  Round::JSONObject *childObject;
  
  // New in version 2.3
  // json_object_foreach(jsonTDict, jsonKey, jsonTObj) {
  for (void *it = json_object_iter(jsonTDict); it; it = json_object_iter_next(jsonTDict, it)) {
    jsonKey = json_object_iter_key(it);
    jsonTObj = json_object_iter_value(it);
    childObject = RoundToJSONObject(jsonParser, jsonTObj);
    parentDict->set(jsonKey, childObject);
    if (json_is_object(jsonTObj)) {
      RoundToJSONObject(jsonParser, dynamic_cast<Round::JSONDictionary *>(childObject), jsonTObj);
    } else if (json_is_array(jsonTObj)) {
      RoundToJSONObject(jsonParser, dynamic_cast<Round::JSONArray *>(childObject), jsonTObj);
    }
  }
}

static void RoundToJSONObject(Round::JSONParser *jsonParser, Round::JSONArray *parentArray, json_t *jsonTArray) {
  if (!jsonParser || !parentArray)
    return;
  
  size_t jsonIdx;
  json_t *jsonTObj;
  Round::JSONObject *childObject;

  // New in version 2.5.
  // json_array_foreach(jsonTArray, jsonIdx, jsonTObj) {
  size_t jsonTObjCnt = json_array_size(jsonTArray);
  for (jsonIdx =0; jsonIdx < jsonTObjCnt; jsonIdx++) {
    jsonTObj = json_array_get(jsonTArray, jsonIdx);
    childObject = RoundToJSONObject(jsonParser, jsonTObj);
    parentArray->add(childObject);
    if (json_is_object(jsonTObj)) {
      RoundToJSONObject(jsonParser, dynamic_cast<Round::JSONDictionary *>(childObject), jsonTObj);
    } else if (json_is_array(jsonTObj)) {
      RoundToJSONObject(jsonParser, dynamic_cast<Round::JSONArray *>(childObject), jsonTObj);
    }
  }
}

bool Round::JSONParser::parse(const std::string &jsonString, JSONObject **jsonRetObject, Error *error) {
  clear();

  if (jsonString.size() <= 0)
    return false;

  json_error_t jsonError;
  json_t *jsonResult = json_loads(jsonString.c_str(), 0, &jsonError);
  if (!jsonResult) {
    error->setCode(jsonError.line);
    std::ostringstream ss;
    ss << "Error : Line " << jsonError.line << " , Pos " << jsonError.position << ", " << jsonError.text;
    error->setMessage(ss.str());
    return false;
  }

  this->rootObject = RoundToJSONObject(this, jsonResult);
  if (json_is_object(jsonResult)) {
    RoundToJSONObject(this, dynamic_cast<JSONDictionary *>(this->rootObject), jsonResult);
  } else if (json_is_array(jsonResult)) {
    RoundToJSONObject(this, dynamic_cast<JSONArray *>(this->rootObject), jsonResult);
  }
  
  json_decref(jsonResult);
  
  return true;
}

#endif
