/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
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
  this->msgSem = new Semaphore(0);
}

Round::MessageManager::~MessageManager() {
  delete this->msgSem;
  delete this->msgQueue;
}

bool Round::MessageManager::pushMessage(const Message *msg) {
  if (!msg)
    return false;

  this->msgQueue->pushMessage(msg);
  this->msgSem->post();

  return true;
}

bool Round::MessageManager::waitMessage(const Message **msg) {
  if (!msg)
    return false;

  *msg = NULL;
  if  (this->msgSem->wait() == false)
    return false;
  
  return this->msgQueue->popMessage(msg);
}
