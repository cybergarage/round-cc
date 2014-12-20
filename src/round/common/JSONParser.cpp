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

Round::JSONParser::JSONParser() {
  this->jsonObject = NULL;
}

Round::JSONParser::~JSONParser() {
  clear();
}

void Round::JSONParser::clear() {
  if (this->jsonObject) {
    delete this->jsonObject;
    this->jsonObject = NULL;
  }
}

Round::JSONObject *Round::JSONParser::popObject() {
  JSONObject *popObject = this->jsonObject;
  this->jsonObject = NULL;
  return popObject;
}

bool Round::JSONParser::parse(const std::string &jsonString) {
  return parse(jsonString, &this->jsonObject);
}
