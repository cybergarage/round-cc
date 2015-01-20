/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/Thread.h>

Round::ThreadManager::ThreadManager() {
}

Round::ThreadManager::~ThreadManager() {
  stop();
}

void Round::ThreadManager::addThread(ThreadCore *thread) {
  this->threadList.addThread(thread);
}

bool Round::ThreadManager::start() {
  return this->threadList.start();
}

bool Round::ThreadManager::stop() {
  return this->threadList.stop();
}
