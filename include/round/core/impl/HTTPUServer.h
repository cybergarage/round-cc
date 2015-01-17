/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_HTTPUSERVER_H_
#define _ROUNDCC_HTTPUSERVER_H_

#include <uhttp/util/Thread.h>
#include <mupnp/ssdp/HTTPUSocket.h>
#include <mupnp/ssdp/SSDPSearchResponse.h>
#include <mupnp/ssdp/SSDPSearchRequest.h>

namespace Round {

class HTTPUServer : public mUPnP::HTTPUSocket, public uHTTP::Thread {

 public:

  HTTPUServer();
  ~HTTPUServer();

  void run();
};

}

#endif


