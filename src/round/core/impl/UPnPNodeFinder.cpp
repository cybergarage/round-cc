/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Random.h>
#include <round/core/impl/UPnPNodeFinder.h>
#include <round/core/impl/UPnPServerNode.h>
#include <round/core/RemoteNode.h>
#include <round/core/Log.h>

////////////////////////////////////////////////
//  UPnPNodeFinder
////////////////////////////////////////////////

int Round::UPnPNodeFinder::HTTP_PORT_RANGE_MIN = 4004;
int Round::UPnPNodeFinder::HTTP_PORT_RANGE_MAX = 9999;

Round::UPnPNodeFinder::UPnPNodeFinder() {
  Random randomPort(HTTP_PORT_RANGE_MIN, HTTP_PORT_RANGE_MAX);
  this->upnpControlPoint.setHTTPPort(randomPort.rand());
  
  this->upnpControlPoint.addDeviceChangeListener(this);
  this->upnpControlPoint.addNotifyListener(this);
  this->upnpControlPoint.addSearchResponseListener(this);
}

Round::UPnPNodeFinder::~UPnPNodeFinder() {
}

bool Round::UPnPNodeFinder::start(Error *error) {
  if (!this->upnpControlPoint.start()) {
    error->setCode(ServerErrorCannotStartControlPoint);
    return false;
  }

  if (!search(error))
    return false;
  
  return true;
}

bool Round::UPnPNodeFinder::stop(Error *error) {
  if (!this->upnpControlPoint.stop()) {
    error->setCode(ServerErrorCannotStartControlPoint);
    return false;
  }

  return true;
}

bool Round::UPnPNodeFinder::search(Error *error) {
  if (!this->upnpControlPoint.search()) {
    error->setCode(ServerErrorCannotSearchDevice);
    return false;
  }
  
  return true;
}

bool Round::UPnPNodeFinder::addRemoteNode(const std::string &remoteHost, int remotePort) {
  if (remoteHost.length() <= 0 || remotePort <= 0)
    return false;
  
  RemoteNode remoteNode(remoteHost, remotePort);
  return postNodeAdded(&remoteNode);
}

bool Round::UPnPNodeFinder::addRemoteNode(mUPnP::SSDPPacket *ssdpPacket) {
  std::string nt;
  ssdpPacket->getNT(nt);
  
  LogTrace("addRemoteNode : %s", nt.c_str());

  if (!UPnPServerNode::IsRoundDeviceType(nt))
    return false;
  
  return addRemoteNode(
                       ssdpPacket->getRemoteAddress(),
                       ssdpPacket->getRemotePort());
}

bool Round::UPnPNodeFinder::removeRemoteNode(const std::string &remoteHost, int remotePort) {
  if (remoteHost.length() <= 0 || remotePort <= 0)
    return false;
  
  RemoteNode remoteNode(remoteHost, remotePort);
  return postNodeRemoved(&remoteNode);
}

bool Round::UPnPNodeFinder::deviceAdded(mUPnP::Device * dev) {
  std::string devType = dev->getDeviceType();
  if (!UPnPServerNode::IsRoundDeviceType(devType))
    return false;
  
  std::string devLocation = dev->getLocation();
  if (devLocation.length() <= 0)
    return false;
  
  uHTTP::URL devURL(devLocation);
  return addRemoteNode(
                devURL.getHost(),
                devURL.getPort());
}

bool Round::UPnPNodeFinder::deviceRemoved(mUPnP::Device * dev) {
  if (!UPnPServerNode::IsRoundDeviceType(dev->getDeviceType()))
    return false;
  
  std::string devLocation = dev->getLocation();
  if (devLocation.length() <= 0)
    return false;
  
  uHTTP::URL devURL(devLocation);
  return removeRemoteNode(
                   devURL.getHost(),
                   devURL.getPort());

}

bool Round::UPnPNodeFinder::deviceNotifyReceived(mUPnP::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}

bool Round::UPnPNodeFinder::deviceSearchResponseReceived(mUPnP::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}
