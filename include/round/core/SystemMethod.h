/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SYSTEMMETHOD_H_
#define _ROUNDCC_SYSTEMMETHOD_H_

#include <round/core/NodeMessage.h>

namespace Round {

/**
 * SystemMethodResponse uses to create a response message for system methods.
 */

class SystemMethodRequest : public NodeRequest {
 public:
  static const std::string PREFIX;
  
  static const std::string SET_METHOD;
  static const std::string GET_NODE_INFO;
  static const std::string GET_CLUSTER_INFO;
  static const std::string GET_NETWORK_INFO;
  
  static const std::string LANGUAGE;
  static const std::string NAME;
  static const std::string CODE;
  
 public:
  SystemMethodRequest();

 private:
};

class SystemGetNodeInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNodeInfoRequest() {
    setMethod(GET_NODE_INFO);
  }
};

class SystemGetClusterInfoRequest : public SystemMethodRequest {
 public:
  SystemGetClusterInfoRequest() {
      setMethod(GET_CLUSTER_INFO);
  }
};

class SystemGetNetworkInfoRequest : public SystemMethodRequest {
 public:
  SystemGetNetworkInfoRequest() {
    setMethod(GET_NETWORK_INFO);
  }
};
  
/**
 * SystemMethodResponse uses to create a response message for system methods.
 */

class SystemMethodResponse {
  public:
    static const std::string NAME;
    static const std::string IP;
    static const std::string PORT;
    static const std::string HASH;
    static const std::string VERSION;
    static const std::string CLUSTER;
    static const std::string CLUSTERS;
    
public:
    SystemMethodResponse(NodeResponse *nodeRes);
    
 protected:
    NodeResponse *nodeRes;
};
  
class SystemGetNodeInfoResponse : public SystemMethodResponse {
 public:
  SystemGetNodeInfoResponse(NodeResponse *nodeRes) : SystemMethodResponse(nodeRes) {
  }

  bool setIp(const std::string &value) {
    return nodeRes->setResult(IP, value);
  }
  
  bool getIp(std::string *value) const {
    return nodeRes->getResult(IP, value);
  }

  bool setPort(int value) {
    return nodeRes->setResult(PORT, value);
  }
  
  bool getPort(int *value) const {
    return nodeRes->getResult(PORT, value);
  }
  
  bool setCluster(const std::string &value) {
    return nodeRes->setResult(CLUSTER, value);
  }
  
  bool getCluster(std::string *value) const {
    return nodeRes->getResult(CLUSTER, value);
  }

  bool setHash(const std::string &value) {
    return nodeRes->setResult(HASH, value);
  }
  
  bool getHash(std::string *value) const {
    return nodeRes->getResult(HASH, value);
  }
};


}

#endif
