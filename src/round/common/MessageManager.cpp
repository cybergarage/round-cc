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

#include <errno.h>
extern int errno;

#include <round/common/JSON.h>
#include <round/common/Message.h>

#define FRACTAL_MESSAGE_MAXSIZE 1024

Round::MessageManager::MessageManager() {
  this->msgQueue = new MessageQueue();
  this->msgSem = new Semaphore(1);
}

Round::MessageManager::~MessageManager() {
  delete this->msgSem;
  delete this->msgQueue;
}

bool Round::MessageManager::pushMessage(const Message *message) {
  if (!message)
    return false;

  this->msgQueue->pushMessage(message);
  this->msgSem->post();

  return true;
}

bool Round::MessageManager::popMessage(Message *message) {
  if (!message)
    return false;

  if  (this->msgSem->wait() == false)
    return false;
  
  return this->msgQueue->popMessage(message);
}
