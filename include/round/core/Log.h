/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_LOG_H_
#define _ROUNDCC_LOG_H_

#include <uhttp/util/Log.h>
#include <round/core/Logger.h>
#include <round/core/LoggerTarget.h>
#include <round/common/Error.h>

namespace Round {
#if defined(DEBUG)
#define RoundLogTrace(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define RoundLogInfo(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define RoundLogWarn(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define RoundLogError(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define RoundLogFatal(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define RoundLogDebug(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::DBG,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#else
#define RoundLogTrace(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE,   format, ##__VA_ARGS__)
#define RoundLogInfo(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO,    format, ##__VA_ARGS__)
#define RoundLogWarn(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN,    format, ##__VA_ARGS__)
#define RoundLogError(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR,     format, ##__VA_ARGS__)
#define RoundLogFatal(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL,   format, ##__VA_ARGS__)
#define RoundLogDebug(format, ...)
#endif

inline int RoundLog(const Round::Error &error) {
#if defined(DEBUG)
  return uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR, __FILE__,  __LINE__, __PRETTY_FUNCTION__, "%s", error.getMessage());
#else
  return uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR, "%s", error.getMessage());
#endif
}

}

#endif
