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

bool Round::MessageQueue::pushMessage(const std::string &message) {
  this->mutex.lock();
  push(message);
  this->mutex.unlock();

  return true;
}

bool Round::MessageQueue::popMessage(std::string *message) {
  if (empty())
    return false;

  this->mutex.lock();
  *message = front();
  pop();
  this->mutex.unlock();

  return true;
}
