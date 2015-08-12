/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_DOMAIN_SOCKET_H_
#define _ROUNDCC_DOMAIN_SOCKET_H_

#include <string>
#include <uhttp/net/Socket.h>

namespace Round {

class DomainSocket : public uHTTP::Socket {

 public:
  DomainSocket();
  ~DomainSocket();
  
  bool connect(const std::string &filename);

  void setFilename(const std::string &filename) {
    this->filename = filename;
  }
  
  const char *getFilename() {
    return this->filename.c_str();
  }
  
private:

  std::string filename;
};

class DomainServerSocket : public DomainSocket {
    
public:
  DomainServerSocket();
  ~DomainServerSocket();
    
  bool open(const std::string &filename);
  bool close();

private:
  bool bind(const std::string &filename);
};
  
}

#endif
