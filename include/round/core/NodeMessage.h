/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEMESSAGE_H_
#define _ROUNDCC_NODEMESSAGE_H_

#include <round/common/RPC.h>

namespace Round {

class NodeResponse;
  
class NodeRequest : public RPC::JSON::Request {
 public:
  
  NodeRequest();
  NodeRequest(const std::string &method);
  virtual ~NodeRequest();
 
  bool hasMethod() const;
  bool isMethod(const std::string &method) const;
  bool isValid();
  
  bool setHttpRequest(uHTTP::HTTPRequest *httpReq);
  uHTTP::HTTPRequest *getHttpRequest() const {return this->httpReq;}
  
  void setResponse(NodeResponse *nodeRes) {this->nodeRes = nodeRes;}
  NodeResponse *getResponse() const {return this->nodeRes;}

 private:
  
  uHTTP::HTTPRequest *httpReq;
  NodeResponse       *nodeRes;

  void init();
  bool close();
};

class NodeResponse : public RPC::JSON::Response {
public:
  NodeResponse();
  virtual ~NodeResponse();
};
  
class NodeMessageRequestParser : public JSONParser {
    
  public:
    
  NodeMessageRequestParser() {
  }
  
  JSONDictionary *createJSONDictionary() {
    return new NodeRequest();
  }
};

class NodeMessageManager : public MessageManager {
 public:
  NodeMessageManager() {
  }
};
  
}

#endif
