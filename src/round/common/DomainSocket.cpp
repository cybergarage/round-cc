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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

Round::DomainSocket::DomainSocket() {
}

Round::DomainSocket::~DomainSocket() {
}

bool Round::DomainSocket::connect(const std::string &filename) {
  int sock = socket(PF_UNIX, SOCK_STREAM, 0);
  if (sock == -1)
    return false;
  
  struct sockaddr_un sockAddr;
  memset(&sockAddr, 0, sizeof(struct sockaddr_un));
  sockAddr.sun_family = AF_UNIX;
  strcpy(sockAddr.sun_path, filename.c_str());
  
  size_t ret = ::connect(sock, (struct sockaddr *)&sockAddr, sizeof(sockaddr_un));
  if (ret != 0) {
    setErrorCode(errno);
    return false;
  }
  
  setSocket(sock);
  setFilename(filename);
  
  return true;
}
