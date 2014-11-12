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

class Message : public JSONDictionary {
  
public:
  
  Message();
  ~Message();

  void setClock(const Clock &clock);
  bool hasClock() const;
  bool getClock(Clock *clock) const;
};

class MessageQueue : private std::queue<std::string> {
  
public:
  
  MessageQueue();
  virtual ~MessageQueue();
  
  bool pushMessage(const std::string &message);
  bool popMessage(std::string *message);
  
private:
  
  void clear();

private:

  Mutex mutex;
};

class MessageManager {
 public:
  MessageManager();
  virtual ~MessageManager();

  bool pushMessage(const Message *message);
  bool popMessage(Message *message);

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
