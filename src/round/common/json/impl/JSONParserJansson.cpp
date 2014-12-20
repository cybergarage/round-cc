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

static Round::JSONObject *RoundToJSONObject(Round::JSONParser *jsonParser, json_t jsonObj) {
  switch (json_typeof(jsonObj)) {
  case JSON_OBJECT:
    return jsonParser->createJSONDictionay();
  case JSON_ARRAY:
    return jsonParser->createJSONArray();
  case JSON_STRING:
    return jsonParser->createJSONArray();
  }
  return new JSONNull();
}

bool Round::JSONParser::parse(const std::string &jsonString, JSONObject **jsonRetObject, Error *error) {
  clear();

  if (jsonString.size() <= 0)
    return false;

  json_error_t jsonError;
  json_t *jsonResult = json_loads(jsonString.c_str(), 0, &jsonError);
  if (!jsonResult) {
    return false;
  }

  json_decref(jsonResult);
  
  return true;
}

#endif
