/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_MESSAGE_H_
#define _ROUNDCC_MESSAGE_H_

#include <queue>

#include <uhttp/http/HTTPRequest.h>

#include <round/common/Clock.h>
#include <round/common/JSON.h>
#include <round/common/Mutex.h>
#include <round/common/Semaphore.h>

namespace Round {

typedef int MessageType;
  
class Message {
  
public:
  
  Message();
  virtual ~Message();
  
  bool setHttpRequest(uHTTP::HTTPRequest *httpReq);
  
  uHTTP::HTTPRequest *getHttpRequest() const {
    return this->httpReq;
  }
  
private:
  
  void init();
  bool close();

private:
  
  mutable uHTTP::HTTPRequest *httpReq;
};

class Request : public Message, public JSONDictionary {
    
  public:
    
  Request() {}
  virtual ~Request() {}
};

class BatchRequest : public Message, public JSONArray {
    
  public:
    
    BatchRequest() {}
    virtual ~BatchRequest() {}
};

class MessageQueue : private std::queue<const Message *> {
  
public:
  
  MessageQueue();
  virtual ~MessageQueue();
  
  bool pushMessage(const Message *msg);
  bool popMessage(const Message **msg);
  
private:
  
  void clear();

private:

  Mutex mutex;
};

class MessageManager {
 public:
  MessageManager();
  virtual ~MessageManager();

  bool pushMessage(const Message *msg);
  bool waitMessage(const Message **msg);

 private:

  void init();
  void clear();

 private:
 
  Semaphore *msgSem;
  MessageQueue *msgQueue;
};

}

#endif
