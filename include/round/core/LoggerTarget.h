/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_LOGGERTARGET_H_
#define _ROUNDCC_LOGGERTARGET_H_

#include <uhttp/util/LoggerTarget.h>
#include <uhttp/util/LoggerFileTarget.h>
#include <uhttp/util/LoggerStdTarget.h>

namespace Round {
class LoggerLevel : public uHTTP::LoggerLevel {
};

class LoggerFileTarget : public uHTTP::LoggerFileTarget {
 public:
  LoggerFileTarget() {
  }
};

class LoggerStdFileTarget : public LoggerFileTarget {
  public:
  LoggerStdFileTarget() {
    setMask(
            LoggerTarget::TRACE  |
            LoggerTarget::DBG    |
            LoggerTarget::INFO
            );
  }
};

class LoggerErrorFileTarget : public LoggerFileTarget {
  public:
  LoggerErrorFileTarget() {
    setMask(
            LoggerTarget::WARN  |
            LoggerTarget::ERR   |
            LoggerTarget::FATAL
            );
  }
};

class LoggerStdoutTarget : public uHTTP::LoggerStdoutTarget {
 public:
  LoggerStdoutTarget() {
  }
};

class LoggerStderrTarget : public uHTTP::LoggerStderrTarget {
 public:
  LoggerStderrTarget() {
  }
};

}

#endif
