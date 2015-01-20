/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEUPNPSERVER_H_
#define _ROUNDCC_NODEUPNPSERVER_H_

#include <string>

#include <mupnp/Device.h>
#include <mupnp/ControlPoint.h>

#include <round/Finder.h>
#include <round/core/ServerNode.h>
#include <round/core/impl/HTTPUServer.h>

namespace Round {

class UPnPServerNode : public ServerNode, public mUPnP::Device {
 public:
  static const std::string DEVICE_TYPE;

  static int HTTP_PORT_RANGE_MIN;
  static int HTTP_PORT_RANGE_MAX;
  
  public:
  
  static bool IsRoundDeviceType(const std::string &deviceType) {
    return (deviceType.compare(UPnPServerNode::DEVICE_TYPE) == 0) ? true : false;
  }
  
 public:
  UPnPServerNode();
  virtual ~UPnPServerNode();

  bool start(Error *error);
  bool stop(Error *error);

  void deviceAdded(mUPnP::Device * dev);
  void deviceRemoved(mUPnP::Device * dev);
  void deviceNotifyReceived(mUPnP::SSDPPacket *ssdpPacket);
  void deviceSearchResponseReceived(mUPnP::SSDPPacket *ssdpPacket);

private:

  mUPnP::Service *getNodeService();

  bool actionControlReceived(mUPnP::Action *action);
  bool queryControlReceived(mUPnP::StateVariable *stateVar);
  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

  bool initDevice();

private:

  bool initialized;

  Finder nodeFinder;
  HTTPUServer httpuServer;
};

}

#endif
