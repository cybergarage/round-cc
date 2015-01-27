/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SERVER_H_
#define _ROUNDCC_SERVER_H_

#include <round/core/Logger.h>
#include <round/core/impl/UPnPServerNode.h>

namespace Round {

class Server : public UPnPServerNode {
 public:
  static int DEFAULT_HTTPD_PORT;

 public:
  Server();
  virtual ~Server();

  bool getLogFilename(std::string *value, Error *error);

  Logger *getLogger() {
    return &logger;
  }

  virtual void initialize() {};
  virtual void finalize() {};
  
private:

  static Logger logger;
};

}

#endif
