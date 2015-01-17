/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_ERROR_H_
#define _ROUNDCC_ERROR_H_

#include <string>

namespace Round {

class Error {

 public:
  Error();
  Error(int code);
  Error(int code, const std::string &message);
  Error(int code, const std::string &message, int detailCode, const std::string &detailMessage);

  virtual ~Error();

  bool isError();

  void setCode(int value) {
    this->code = value;
  }

  void setMessage(const std::string &value) {
    this->message = value;
  }

  int getCode() const {
    return this->code;
  }

  const char *getMessage() const {
    return this->message.c_str();
  }

  void setDetailCode(int value) {
    this->detailCode = value;
  }
  
  void setDetailMessage(const std::string &value) {
    this->detailMessage = value;
  }
  
  int getDetailCode() const {
    return this->detailCode;
  }
  
  const char *getDetailMessage() const {
    return this->detailMessage.c_str();
  }
  
  bool equals(const Error &err) const;

 private:

  void initialize();
  
  int code;
  std::string message;

  int detailCode;
  std::string detailMessage;
};

}

#endif
