/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CLIENT_H_
#define _ROUNDCC_CLIENT_H_

#include <round/core/ClientCore.h>
#include <round/Finder.h>

namespace Round {
  
class Client : public ClientCore {
  
public:
  
  Client();
  virtual ~Client();

  bool start(Error *error);
  bool stop(Error *error);
  bool search(Error *error);

  void setFinderEnabled(bool flag) {
    this->finder.setEnabled(flag);
  }
  
  bool finderEnabled() {
    return this->finder.isEnabled();
  }
  
private:
  
  Finder finder;
};

}

#endif
