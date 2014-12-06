/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#include <round/common/Message.h>

Round::MessageQueue::MessageQueue() {
}

Round::MessageQueue::~MessageQueue() {
}

bool Round::MessageQueue::pushMessage(const Message *msg) {
  if (!msg)
    return false;
  
  this->mutex.lock();
  push(msg);
  this->mutex.unlock();

  return true;
}

bool Round::MessageQueue::popMessage(const Message **msg) {
  if (!msg)
    return false;
  
  if (empty())
    return false;

  this->mutex.lock();
  
  *msg = front();
  pop();
  
  this->mutex.unlock();
  
  return true;
}
