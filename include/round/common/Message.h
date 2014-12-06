/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_MESSAGE_H_
#define _ROUNDCC_MESSAGE_H_

#include <queue>

#include <round/common/Clock.h>
#include <round/common/JSON.h>
#include <round/common/Mutex.h>
#include <round/common/Semaphore.h>

namespace Round {

typedef int MessageType;
  
class Message : public JSONDictionary {
  
public:
  
  Message();
  ~Message();
};

class MessageQueue : private std::queue<Message *> {
  
public:
  
  MessageQueue();
  virtual ~MessageQueue();
  
  bool pushMessage(Message *msg);
  bool popMessage(Message **msg);
  
private:
  
  void clear();

private:

  Mutex mutex;
};

class MessageManager {
 public:
  MessageManager();
  virtual ~MessageManager();

  bool pushMessage(Message *msg);
  bool popMessage(Message **msg);

 private:

  void init();
  void clear();

  bool hasId();
  int getId();

 private:
 
  Semaphore *msgSem;
  MessageQueue *msgQueue;
};

}

#endif
