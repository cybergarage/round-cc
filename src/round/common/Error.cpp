/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/common/Error.h>

Round::Error::Error() {
  initialize();
  this->code = 0;
}

Round::Error::Error(int code) {
  initialize();
  this->code = code;
}

Round::Error::Error(int code, const std::string &message) {
  initialize();
  this->code = code;
  this->message = message;
}

Round::Error::Error(int code, const std::string &message, int detailCode, const std::string &detailMessage) {
  initialize();
  this->code = code;
  this->message = message;
  this->detailCode = detailCode;
  this->detailMessage = detailMessage;
}

void Round::Error::initialize() {
  this->code = 0;
  this->detailCode = 0;
}

Round::Error::~Error() {
}

bool Round::Error::isError() {
  if (0 < this->code)
    return true;
  return false;
}

bool Round::Error::equals(const Error &other) const {
  if (this->getCode() != other.getCode())
    return false;

  if (this->message.compare(other.getMessage()) != 0)
    return false;
  
  return true;
}

