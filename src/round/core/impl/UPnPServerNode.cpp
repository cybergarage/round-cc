/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <string.h>

#include <uhttp/net/URL.h>
#include <round/common/Random.h>
#include <round/core/Log.h>
#include <round/core/impl/UPnPServerDesc.h>
#include <round/core/impl/UPnPServerNode.h>


////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const std::string Round::UPnPServerNode::DEVICE_TYPE = ROUNDCC_UPNP_DEVICE_TYPE;
const std::string Round::UPnPServerNode::SERVICE_TYPE = ROUNDCC_UPNP_SERVICE_TYPE;

static const std::string FRACTAL_NODESERVER_DESCRIPTION_URI = "description/description.xml";
static const std::string FRACTAL_NODESERVER_PRESENTATION_URI = "/presentation";

static const std::string FRACTAL_NODESERVER_ACTION_GETSTATUS = "GetStatus";
static const std::string FRACTAL_NODESERVER_ACTION_GETSTATUS_VERSION = "Version";

////////////////////////////////////////////////
//  UPnPServerNode
////////////////////////////////////////////////

Round::UPnPServerNode::UPnPServerNode() : Device() {
  this->initialized = initDevice();
  nodeFinder.addObserver(this);
}

Round::UPnPServerNode::~UPnPServerNode() {
}

bool Round::UPnPServerNode::initDevice() {
  if (loadDescription(FRACTAL_NODESERVER_DEVICE_DESCRIPTION) == false)
    return false;

  mUPnP::Service *nodeService = getNodeService();
  if (!nodeService)
    return false;
  
  if (nodeService->loadSCPD(FRACTAL_NODESERVER_SERVICE_NODE_DESCRIPTION) == false)
    return false;

  setLeaseTime(60 * 30);

  return true;
}

mUPnP::Service *Round::UPnPServerNode::getNodeService() {
  return getService(SERVICE_TYPE);
}

bool Round::UPnPServerNode::start(Error *error) {
  if (!this->initialized)
    return false;
  
  if (ServerNode::start(error) == false)
    return false;
  
  // Config
  
  std::string localAddress;
  if (!getConfig()->getBindAddress(&localAddress, error))
    return false;

  int localPort;
  if (!getConfig()->getBindPort(&localPort, error))
    return false;
  
  Device::setHTTPPort(localPort);
  
  // Node Finder

  if (this->nodeFinder.start(error) == false)
    return false;

  // Device

  if (Device::start() == false)
    return false;

  int httpPort = Device::getHTTPPort();
  setRequestAddress(localAddress);
  setRequestPort(httpPort);

  // HTTPU Server
  
  if (!httpuServer.open(httpPort, localAddress))
    return false;
  
  if (!httpuServer.start())
    return false;
  
  // State
  setState(NodeStatus::ACTIVE);

  RoundLogInfo("Node (%s:%d) is started", localAddress.c_str(), httpPort);
  
  return true;
}

bool Round::UPnPServerNode::stop(Error *error) {
  bool isSuccess = true;

  if (ServerNode::stop(error) == false)
    isSuccess = false;
  
  if (Device::stop() == false)
    isSuccess = false;

  if (this->nodeFinder.stop(error) == false)
    isSuccess = false;

  if (!httpuServer.stop())
    isSuccess = false;
  
  if (isSuccess == true)
    setState(NodeStatus::STOP);

  RoundLogInfo("Node is stopped");
  
  return isSuccess;
}

bool Round::UPnPServerNode::actionControlReceived(mUPnP::Action *action) {
  const std::string actionName = action->getName();

  if (boost::iequals(actionName, FRACTAL_NODESERVER_ACTION_GETSTATUS)) {
    Round::Error error;
    std::string version;
    if (!getVersion(&version, &error))
      return false;
    action->setArgumentValue(FRACTAL_NODESERVER_ACTION_GETSTATUS_VERSION, version);
    return true;
  }

  return false;
}

bool Round::UPnPServerNode::queryControlReceived(mUPnP::StateVariable *stateVar) {
  return false;
}

uHTTP::HTTP::StatusCode Round::UPnPServerNode::httpRequestRecieved(uHTTP::HTTPRequest *httpReq) {
  if (isRpcRequest(httpReq)) {
    return ServerNode::httpRpcRequestReceived(httpReq);
  }
  
  return Device::httpRequestRecieved(httpReq);
}
