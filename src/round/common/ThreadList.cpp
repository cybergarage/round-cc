/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <round/common/Thread.h>

Round::ThreadList::ThreadList() {
}

Round::ThreadList::~ThreadList() {
  clear();
}

void Round::ThreadList::addThread(ThreadCore *thread) {
  push_back(thread);
}

void Round::ThreadList::clear() {
  stop();
  for (ThreadList::iterator thread = begin(); thread != end(); thread++) {
    delete (*thread);
  }
  std::vector<ThreadCore *>::clear();
}

bool Round::ThreadList::start() {
  bool allThreadsStarted = true;
  for (ThreadList::iterator thread = begin(); thread != end(); thread++) {
    if ((*thread)->start() == false)
      allThreadsStarted = false;
  }
  return allThreadsStarted;
}

bool Round::ThreadList::stop() {
  bool allThreadsStopped = true;
  for (ThreadList::iterator thread = begin(); thread != end(); thread++) {
    if ((*thread)->stop() == false)
      allThreadsStopped = false;
  }
  return allThreadsStopped;
}
