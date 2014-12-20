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
