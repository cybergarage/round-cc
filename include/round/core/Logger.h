/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/


#ifndef _ROUNDCC_LOGGER_H_
#define _ROUNDCC_LOGGER_H_

#include <uhttp/util/Logger.h>

namespace Round {

class Logger : public uHTTP::Logger {

 public:
  static bool HasSharedInstance();
  static Logger *GetSharedInstance();

 public:
  Logger();
  ~Logger();

};

}

#endif
