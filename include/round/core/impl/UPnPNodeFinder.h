/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEUPNPFINDER_H_
#define _ROUNDCC_NODEUPNPFINDER_H_

#include <round/core/NodeFinder.h>
#include <cybergarage/upnp/ControlPoint.h>

namespace Round {

class UPnPNodeFinder : public NodeFinder, public CyberLink::NotifyListener, public CyberLink::SearchResponseListener, public CyberLink::DeviceChangeListener {

public:
  
  static int HTTP_PORT_RANGE_MIN;
  static int HTTP_PORT_RANGE_MAX;
  
public:
  UPnPNodeFinder();
  virtual ~UPnPNodeFinder();

  bool start(Error *error);
  bool stop(Error *error);
  bool search(Error *error);
  
  bool deviceAdded(CyberLink::Device * dev);
  bool deviceRemoved(CyberLink::Device * dev);
  bool deviceNotifyReceived(CyberLink::SSDPPacket *ssdpPacket);
  bool deviceSearchResponseReceived(CyberLink::SSDPPacket *ssdpPacket);

  void setEnabled(bool flag) {
    this->enabled = flag;
  }
  
  bool isEnabled() {
    return this->enabled;
  }
  
private:
  
  bool addRemoteNode(const std::string &remoteHost, int remotePort);
  bool addRemoteNode(CyberLink::SSDPPacket *ssdpPacket);
  bool removeRemoteNode(const std::string &remoteHost, int remotePort);

private:
  
  CyberLink::ControlPoint upnpControlPoint;
  bool enabled;
};

}

#endif
