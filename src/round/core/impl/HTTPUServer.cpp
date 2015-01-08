/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/core/impl/HTTPUServer.h>

Round::HTTPUServer::HTTPUServer() {
}
  
Round::HTTPUServer::~HTTPUServer() {
  stop();
  close();
}

void Round::HTTPUServer::run() {
  while (isRunnable() == true) {
    mUPnP::SSDPPacket ssdpPacket;
    if (!receive(&ssdpPacket))
      break;
  }
}
