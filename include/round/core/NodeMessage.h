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
   
  bool setHttpRequest(uHTTP::HTTPRequest *httpReq);
  uHTTP::HTTPRequest *getHttpRequest() const {return this->httpReq;}
  
 private:
  
  mutable uHTTP::HTTPRequest *httpReq;

  void init();
  bool close();
};

class NodeResponse : public RPC::JSON::Response {
public:
  NodeResponse();
  virtual ~NodeResponse();
};
  
class NodeRequestParser : public JSONParser {
    
 public:
  NodeRequestParser() {
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
