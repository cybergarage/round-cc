/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <iostream>
#include <sstream>

#include <round/common/JSON.h>

Round::JSONParser::JSONParser() {
  this->rootObject = NULL;
}

Round::JSONParser::~JSONParser() {
  clear();
}

void Round::JSONParser::clear() {
  if (this->rootObject) {
    delete this->rootObject;
    this->rootObject = NULL;
  }
}

Round::JSONObject *Round::JSONParser::popRootObject() {
  JSONObject *popObject = this->rootObject;
  this->rootObject = NULL;
  return popObject;
}

bool Round::JSONParser::parse(const std::string &jsonString, Error *error) {
  return parse(jsonString, &this->rootObject, error);
}
