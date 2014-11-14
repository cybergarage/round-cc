/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/algorithm/string.hpp>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <string.h>

#include <round/Server.h>

#include <uhttp/net/URL.h>

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const std::string Round::Server::DEVICE_TYPE = "urn:cybergarage-org:device:fractal:1";

static const std::string FRACTAL_NODESERVER_DESCRIPTION_URI = "description/description.xml";
static const std::string FRACTAL_NODESERVER_PRESENTATION_URI = "/presentation";
static const std::string FRACTAL_NODESERVER_SERVICE_NODE_TYPE = "urn:cybergarage-org:service:node:1";

static const std::string FRACTAL_NODESERVER_ACTION_GETSTATUS = "GetStatus";
static const std::string FRACTAL_NODESERVER_ACTION_GETSTATUS_VERSION = "Version";

static const std::string FRACTAL_NODESERVER_DEVICE_DESCRIPTION =
"<?xml version=\"1.0\" ?>\n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
"   <specVersion>\n"
"     <major>1</major>\n"
"     <minor>0</minor>\n"
"   </specVersion>\n"
"   <device>\n"
"     <deviceType>urn:cybergarage-org:device:fractal:1</deviceType>\n"
"     <friendlyName>Round</friendlyName>\n"
"     <manufacturer>CyberGarage</manufacturer>\n"
"     <manufacturerURL>http://www.cybergarage.org</manufacturerURL>\n"
"     <modelDescription>Round Server</modelDescription>\n"
"     <modelName>Round</modelName>\n"
"     <modelNumber>1.0</modelNumber>\n"
"     <modelURL>http://www.cybergarage.org</modelURL>\n"
"     <serviceList>\n"
"       <service>\n"
"         <serviceType>urn:cybergarage-org:service:node:1</serviceType>\n"
"         <serviceId>urn:cybergarage-org:serviceId:node:1</serviceId>\n"
"         <SCPDURL>/service/node/description.xml</SCPDURL>\n"
"         <controlURL>/service/node/control</controlURL>\n"
"         <eventSubURL>/service/node/eventSub</eventSubURL>\n"
"       </service>\n"
"     </serviceList>\n"
"     <presentationURL>/presentation</presentationURL>\n"
"  </device>\n"
"</root>\n";

static const std::string FRACTAL_NODESERVER_SERVICE_NODE_DESCRIPTION =
"<?xml version=\"1.0\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">\n"
"   <specVersion>\n"
"     <major>1</major>\n"
"     <minor>0</minor>\n"
"   </specVersion>\n"
"   <actionList>\n"
"     <action>\n"
"       <name>GetStatus</name>\n"
"       <argumentList>\n"
"         <argument>\n"
"           <name>Version</name>\n"
"           <relatedStateVariable>Version</relatedStateVariable>\n"
"           <direction>out</direction>\n"
"         </argument>\n"
"       </argumentList>\n"
"     </action>\n"
"   </actionList>\n"
"   <serviceStateTable>\n"
"     <stateVariable sendEvents=\"no\">\n"
"       <name>Version</name>\n"
"       <dataType>string</dataType>\n"
"     </stateVariable>\n"
"   </serviceStateTable>\n"
"</scpd>\n";

////////////////////////////////////////////////
//  Server
////////////////////////////////////////////////

Round::Server::Server() : Device() {
  this->initialized = initDevice();
  //nodeFinder.addObserver(this);
}

Round::Server::~Server() {
}

bool Round::Server::loadConfigFromString(const std::string &string, Error *error) {
  if (this->nodeConfig.loadFromString(string, error) == false)
    return false;
  return true;
}

bool Round::Server::loadConfigFromFile(const std::string &filename, Error *error) {
  if (this->nodeConfig.loadFromFile(filename, error) == false)
    return false;
  return true;
}

bool Round::Server::isConfigValid(Error *error) {
  return this->nodeConfig.isValid(error);
}

bool Round::Server::initDevice() {
  if (loadDescription(FRACTAL_NODESERVER_DEVICE_DESCRIPTION) == false)
    return false;

  CyberLink::Service *nodeService = getServerService();
  if (!nodeService)
    return false;
  
  if (nodeService->loadSCPD(FRACTAL_NODESERVER_SERVICE_NODE_DESCRIPTION) == false)
    return false;

  setLeaseTime(60 * 30);

  return true;
}

CyberLink::Service *Round::Server::getServerService() {
  return getService(FRACTAL_NODESERVER_SERVICE_NODE_TYPE);
}

bool Round::Server::start(Error *error) {
  if (!this->initialized)
    return false;
  
  // Configuration
  
  std::string localAddress;
  //if (!getServerConfig()->getHttpdBindAddress(&localAddress, error))
  //  return false;

  //int localPort;
  //if (!getServerConfig()->getHttpdBindPort(&localPort, error))
  //  return false;
  //
  //Device::setHTTPPort(localPort);
  
  // Server Finder

  if (this->nodeFinder.start(error) == false)
    return false;

  // Device

  if (Device::start() == false)
    return false;

  ///setRequestAddress(localAddress);
  //setRequestPort(Device::getHTTPPort());

  //setState(ServerStatus::ACTIVE);

  return true;
}

bool Round::Server::stop(Error *error) {
  bool isSuccess = true;

  if (Device::stop() == false)
    isSuccess = false;

  if (this->nodeFinder.stop(error) == false)
    isSuccess = false;

  //if (isSuccess == true)
  //  setState(ServerStatus::STOP);

  return isSuccess;
}

bool Round::Server::actionControlReceived(CyberLink::Action *action) {
  const std::string actionName = action->getName();

  if (boost::iequals(actionName, FRACTAL_NODESERVER_ACTION_GETSTATUS)) {
    Round::Error error;
    std::string version;
    //if (!getVersion(&version, &error))
    //  return false;
    action->setArgumentValue(FRACTAL_NODESERVER_ACTION_GETSTATUS_VERSION, version);
    return true;
  }

  return false;
}

bool Round::Server::queryControlReceived(CyberLink::StateVariable *stateVar) {
  return false;
}

uHTTP::HTTP::StatusCode Round::Server::httpRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  std::string method;
  httpReq->getMethod(method);
  std::string uri;
  httpReq->getURI(uri);
/*
  if (isServerHttpRequest(method, uri)) {
    if (ServerServer::httpRequestRecieved(httpReq))
      return uHTTP::HTTP::OK_REQUEST;
  }
*/
  return Device::httpRequestRecieved(httpReq);
}

bool Round::Server::getLogFilename(std::string *value, Error *error) {
  return false;
}

bool Round::Server::getErrorLogFilename(std::string *value, Error *error) {
  return false;
}

