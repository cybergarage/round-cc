/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/impl/UPnPNodeFinder.h>
#include <round/core/impl/UPnPServerNode.h>
#include <round/core/RemoteNode.h>
#include <round/common/Random.h>

////////////////////////////////////////////////
//  UPnPNodeFinder
////////////////////////////////////////////////

int Round::UPnPNodeFinder::HTTP_PORT_RANGE_MIN = 10000;
int Round::UPnPNodeFinder::HTTP_PORT_RANGE_MAX = 60000;

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

bool Round::UPnPNodeFinder::addRemoteNode(CyberLink::SSDPPacket *ssdpPacket) {
  std::string nt;
  if (!UPnPServerNode::IsRoundDeviceType(ssdpPacket->getNT(nt)))
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

bool Round::UPnPNodeFinder::deviceAdded(CyberLink::Device * dev) {
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

bool Round::UPnPNodeFinder::deviceRemoved(CyberLink::Device * dev) {
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

bool Round::UPnPNodeFinder::deviceNotifyReceived(CyberLink::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}

bool Round::UPnPNodeFinder::deviceSearchResponseReceived(CyberLink::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}
