/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FRACTALCC_ERROR_H_
#define _FRACTALCC_ERROR_H_

#include <string>

namespace Round {

typedef int ErrorCodeType;

class Error {

 public:
  Error();
  Error(ErrorCodeType code);
  Error(ErrorCodeType code, const std::string &message);

  virtual ~Error();

  bool isError();

  void setCode(ErrorCodeType value) {
    this->code = value;
  }

  void setMessage(const std::string &value) {
    this->message = value;
  }

  ErrorCodeType getCode() const {
    return this->code;
  }

  const char *getMessage() const {
    return this->message.c_str();
  }

  void setDetailCode(ErrorCodeType value) {
    this->detailCode = value;
  }
  
  void setDetailMessage(const std::string &value) {
    this->detailMessage = value;
  }
  
  ErrorCodeType getDetailCode() const {
    return this->detailCode;
  }
  
  const char *getDetailMessage() const {
    return this->detailMessage.c_str();
  }
  
  bool equals(const Error &err) const;

 private:

  void initialize();
  
  ErrorCodeType code;
  std::string message;

  ErrorCodeType detailCode;
  std::string detailMessage;
};

}

#endif
