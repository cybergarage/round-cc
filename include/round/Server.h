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
#include <round/core/Logger.h>
#include <round/core/NodeConfig.h>

#include <round/Finder.h>

namespace Round {

class Server : public CyberLink::Device {
 public:
  static const std::string DEVICE_TYPE;

  public:
  
  static bool IsRoundDeviceType(const std::string &deviceType) {
    return (deviceType.compare(Server::DEVICE_TYPE) == 0) ? true : false;
  }
  
 public:
  Server();
  virtual ~Server();

  bool start(Error *error);
  bool stop(Error *error);
  bool restart(Error *error) {
    stop(error);
    return start(error);
  }

  void deviceAdded(CyberLink::Device * dev);
  void deviceRemoved(CyberLink::Device * dev);
  void deviceNotifyReceived(CyberLink::SSDPPacket *ssdpPacket);
  void deviceSearchResponseReceived(CyberLink::SSDPPacket *ssdpPacket);
  
  bool getLogFilename(std::string *value, Error *error);
  bool getErrorLogFilename(std::string *value, Error *error);
  
  Logger *getLogger() {
    return &logger;
  }

  bool loadConfigFromString(const std::string &string, Error *error);
  bool loadConfigFromFile(const std::string &filename, Error *error);
  bool isConfigValid(Error *error);
  
private:

  CyberLink::Service *getServerService();

  bool actionControlReceived(CyberLink::Action *action);
  bool queryControlReceived(CyberLink::StateVariable *stateVar);
  uHTTP::HTTP::StatusCode httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

  bool initDevice();

private:

  bool initialized;

  Finder nodeFinder;
  Logger logger;
  
  //NodeConfig nodeConfig;
};

}

#endif
