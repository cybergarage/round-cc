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

#include <uhttp/HTTP.h>

namespace Round {

class NodeMessage : public RPC::JSON::Message {
public:
  static const std::string KEY_CLOCK;
  
 public:
  NodeMessage();
  virtual ~NodeMessage();

  void setClock(const Clock &clock);
  bool hasClock() const;
  bool getClock(Clock *clock) const;
};

class NodeResponse;
  
class NodeRequest : public NodeMessage {
 public:
  static const std::string KEY_METHOD;
    
 public:
  
  NodeRequest();
  NodeRequest(const std::string &method);
  virtual ~NodeRequest();
 
  bool hasMethod() const;
  bool isMethod(const std::string &method) const;
  bool isValid();
  
  bool setHttpRequest(uHTTP::HTTPRequest *httpReq);
  uHTTP::HTTPRequest *getHttpRequest() {return this->httpReq;}
  
  void setResponse(NodeResponse *nodeRes) {this->nodeRes = nodeRes;}
  NodeResponse *getResponse() {return this->nodeRes;}

 private:
  
  uHTTP::HTTPRequest *httpReq;
  NodeResponse       *nodeRes;

  bool close();
};

class NodeResponse : public NodeMessage {
public:
  static const std::string KEY_ERROR_CODE;
  static const std::string KEY_ERROR_MESSAGE;
    
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
