/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_HTTPUSERVER_H_
#define _ROUNDCC_HTTPUSERVER_H_

#include <uhttp/util/Thread.h>
#include <cybergarage/upnp/ssdp/HTTPUSocket.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponse.h>
#include <cybergarage/upnp/ssdp/SSDPSearchRequest.h>

namespace Round {

class HTTPUServer : public CyberLink::HTTPUSocket, public uHTTP::Thread {

 public:

  HTTPUServer();
  ~HTTPUServer();

  void run();
};

}

#endif


