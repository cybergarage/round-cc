/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEUPNPFINDER_H_
#define _ROUNDCC_NODEUPNPFINDER_H_

#include <round/core/NodeFinder.h>
#include <mupnp/ControlPoint.h>

namespace Round {

class UPnPNodeFinder : public NodeFinder, public mUPnP::NotifyListener, public mUPnP::SearchResponseListener, public mUPnP::DeviceChangeListener {

public:
  
  static int HTTP_PORT_RANGE_MIN;
  static int HTTP_PORT_RANGE_MAX;
  
public:
  UPnPNodeFinder();
  virtual ~UPnPNodeFinder();

  bool start(Error *error);
  bool stop(Error *error);
  bool search(Error *error);
  
  bool deviceAdded(mUPnP::Device * dev);
  bool deviceRemoved(mUPnP::Device * dev);
  bool deviceNotifyReceived(mUPnP::SSDPPacket *ssdpPacket);
  bool deviceSearchResponseReceived(mUPnP::SSDPPacket *ssdpPacket);

  void setEnabled(bool flag) {
    this->enabled = flag;
  }
  
  bool isEnabled() {
    return this->enabled;
  }
  
private:
  
  bool addRemoteNode(const std::string &remoteHost, int remotePort);
  bool addRemoteNode(mUPnP::SSDPPacket *ssdpPacket);
  bool removeRemoteNode(const std::string &remoteHost, int remotePort);

private:
  
  mUPnP::ControlPoint upnpControlPoint;
  bool enabled;
};

}

#endif
