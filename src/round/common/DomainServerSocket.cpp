/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include <round/common/DomainSocket.h>

#include <boost/filesystem.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

Round::DomainServerSocket::DomainServerSocket() {
}

Round::DomainServerSocket::~DomainServerSocket() {
  close();
}

bool Round::DomainServerSocket::bind(const std::string &filename) {
  close();
  
  int sock = socket(PF_UNIX, SOCK_STREAM, 0);
  if (sock == -1)
    return false;
  
  struct sockaddr_un sockAddr;
  memset(&sockAddr, 0, sizeof(struct sockaddr_un));
  sockAddr.sun_family = AF_UNIX;
  strcpy(sockAddr.sun_path, filename.c_str());
  
  size_t ret = ::bind(sock, (struct sockaddr *)&sockAddr, sizeof(sockaddr_un));
  if (ret != 0) {
    setErrorCode(errno);
    return false;
  }

  setSocket(sock);
  setFilename(filename);
  
  return true;
}

bool Round::DomainServerSocket::open(const std::string &filename) {
  if (!bind(filename))
    return false;

  if (!listen()) {
    close();
    return false;
  }

  return true;
}

bool Round::DomainServerSocket::close() {
  bool ret = Socket::close();
  
  if (boost::filesystem::remove(getFilename())) {
    setFilename("");
  }
  
  return ret;
}
