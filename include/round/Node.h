/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEUPNPSERVER_H_
#define _ROUNDCC_NODEUPNPSERVER_H_

#include <string>

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/ControlPoint.h>

#include <round/Finder.h>

namespace Round {

class Node : public CyberLink::Device {
 public:
  static const std::string DEVICE_TYPE;

  public:
  
  static bool IsRoundDeviceType(const std::string &deviceType) {
    return (deviceType.compare(Node::DEVICE_TYPE) == 0) ? true : false;
  }
  
 public:
  Node();
  virtual ~Node();

  bool start(Error *error);
  bool stop(Error *error);

  void deviceAdded(CyberLink::Device * dev);
  void deviceRemoved(CyberLink::Device * dev);
  void deviceNotifyReceived(CyberLink::SSDPPacket *ssdpPacket);
  void deviceSearchResponseReceived(CyberLink::SSDPPacket *ssdpPacket);

private:

  CyberLink::Service *getNodeService();

  bool actionControlReceived(CyberLink::Action *action);
  bool queryControlReceived(CyberLink::StateVariable *stateVar);
  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

  bool initDevice();

private:

  bool initialized;

  Finder nodeFinder;
};

}

#endif
