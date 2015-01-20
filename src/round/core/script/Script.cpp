/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/Script.h>

#include <string.h>

const int Round::Script::ENCODING_NONE = 0;
const int Round::Script::ENCODING_BASE64 = 1;

Round::Script::Script(const std::string &lang) {
  this->language = lang;
  this->code = NULL;
  this->codeLen = 0;
  setEncording(ENCODING_NONE);
}

Round::Script::Script(const std::string &lang, const std::string &name, const std::string &code) {
  this->language = lang;
  this->code = NULL;
  this->codeLen = 0;
  setName(name);
  setCode(code);
  setEncording(ENCODING_NONE);
}

Round::Script::Script(const std::string &lang, const std::string &name, const byte *code, size_t codeLen) {
  this->language = lang;
  this->code = NULL;
  this->codeLen = 0;
  setName(name);
  setCode(code, codeLen);
  setEncording(ENCODING_NONE);
}

Round::Script::~Script() {
  if (this->code) {
    free(this->code);
  }
}

bool Round::Script::setCode(const byte *code, size_t codeLen) {
  if (this->code) {
    free(this->code);
  }
  this->codeLen = 0;
  
  this->code = (byte *)malloc(codeLen);
  if (!this->code)
    return false;

  memcpy(this->code, code, codeLen);
  this->codeLen = codeLen;

  return true;
}

bool Round::Script::setCode(const std::string code) {
  return setCode((const byte *)code.c_str(), (code.length() + 1));
}
