/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/Finder.h>
#include <round/common/Random.h>

////////////////////////////////////////////////
//  Finder
////////////////////////////////////////////////

int Round::Finder::HTTP_PORT_RANGE_MIN = 10000;
int Round::Finder::HTTP_PORT_RANGE_MAX = 60000;

Round::Finder::Finder() {
  Random randomPort(HTTP_PORT_RANGE_MIN, HTTP_PORT_RANGE_MAX);
  this->upnpControlPoint.setHTTPPort(randomPort.rand());
  
  this->upnpControlPoint.addDeviceChangeListener(this);
  this->upnpControlPoint.addNotifyListener(this);
  this->upnpControlPoint.addSearchResponseListener(this);
}

Round::Finder::~Finder() {
}

bool Round::Finder::start(Error *error) {
  if (!this->upnpControlPoint.start()) {
    //error->setCode(ServerErrorCannotStartControlPoint);
    return false;
  }

  if (!search(error))
    return false;
  
  return true;
}

bool Round::Finder::stop(Error *error) {
  if (!this->upnpControlPoint.stop()) {
    //error->setCode(ServerErrorCannotStartControlPoint);
    return false;
  }

  return true;
}

bool Round::Finder::search(Error *error) {
  if (!this->upnpControlPoint.search()) {
    //error->setCode(ServerErrorCannotSearchDevice);
    return false;
  }
  
  return true;
}

bool Round::Finder::addRemoteNode(const std::string &remoteHost, int remotePort) {
  if (remoteHost.length() <= 0 || remotePort <= 0)
    return false;
  
  //RemoteNode remoteNode(remoteHost, remotePort);
  //return postNodeAdded(&remoteNode);
}

bool Round::Finder::addRemoteNode(CyberLink::SSDPPacket *ssdpPacket) {
  std::string nt;
  //if (!UPnPServerNode::IsRoundDeviceType(ssdpPacket->getNT(nt)))
  //  return false;
  
  return addRemoteNode(
                       ssdpPacket->getRemoteAddress(),
                       ssdpPacket->getRemotePort());
}

bool Round::Finder::removeRemoteNode(const std::string &remoteHost, int remotePort) {
  if (remoteHost.length() <= 0 || remotePort <= 0)
    return false;
  
  //RemoteNode remoteNode(remoteHost, remotePort);
  //return postNodeRemoved(&remoteNode);
}

bool Round::Finder::deviceAdded(CyberLink::Device * dev) {
  std::string devType = dev->getDeviceType();
//  if (!UPnPServerNode::IsRoundDeviceType(devType))
//    return false;
  
  std::string devLocation = dev->getLocation();
  if (devLocation.length() <= 0)
    return false;
  
  uHTTP::URL devURL(devLocation);
  return addRemoteNode(
                devURL.getHost(),
                devURL.getPort());
}

bool Round::Finder::deviceRemoved(CyberLink::Device * dev) {
//  if (!UPnPServerNode::IsRoundDeviceType(dev->getDeviceType()))
//    return false;
  
  std::string devLocation = dev->getLocation();
  if (devLocation.length() <= 0)
    return false;
  
  uHTTP::URL devURL(devLocation);
  return removeRemoteNode(
                   devURL.getHost(),
                   devURL.getPort());

}

bool Round::Finder::deviceNotifyReceived(CyberLink::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}

bool Round::Finder::deviceSearchResponseReceived(CyberLink::SSDPPacket *ssdpPacket) {
  return addRemoteNode(ssdpPacket);
}
