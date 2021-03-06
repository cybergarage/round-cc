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
#include <round/core/local/method/SystemMethod.h>

#include <string.h>

const int Round::Script::ENCODING_NONE = ROUNDCC_ENCODING_NONE;
const int Round::Script::ENCODING_BASE64 = ROUNDCC_ENCODING_BASE64;

Round::Script::Script(const std::string &lang) {
  init();
  this->language = lang;
}

Round::Script::Script(const std::string &lang, const std::string &name, const std::string &code) {
  init();
  this->language = lang;
  setName(name);
  setCode(code);
}

Round::Script::Script(const std::string &lang, const std::string &name, const byte *code, size_t codeLen) {
  init();
  this->language = lang;
  setName(name);
  setCode(code, codeLen);
}

void Round::Script::init() {
  this->language = "";
  this->code = NULL;
  this->codeLen = 0;
  setEncording(ENCODING_NONE);
  setNode(NULL);
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

bool Round::Script::isBinaryCode() {
  for (size_t n=0; n<this->codeLen; n++) {
    byte c = this->code[n];
    if ((c < 0x20) || (0x7E < c)) {
      return true;
    }
  }
  return false;
}

bool Round::Script::toJSONDictionary(JSONDictionary **jsonDict) {
  (*jsonDict)->set(set_method::METHOD_NAME, getName());
  (*jsonDict)->set(set_method::METHOD_LANGUAGE, getLanguage());
  (*jsonDict)->set(set_method::METHOD_CODE, (const char *)(getCode()));
  if (hasEncording()) {
    (*jsonDict)->set(set_method::METHOD_ENCODE, getEncording());
  }
  return true;
}
