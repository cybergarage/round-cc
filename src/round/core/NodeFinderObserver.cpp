/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/NodeFinder.h>

Round::NodeFinderObserver::NodeFinderObserver() {
}

Round::NodeFinderObserver::~NodeFinderObserver() {
}

bool Round::NodeFinderObserver::notificationReceived(NotificationType type, void *object) {
switch (type) {
  case NodeFinderObserverTypeAdd:
    return nodeAdded((Round::Node *)object);
  case NodeFinderObserverTypeRemove:
    return nodeRemoved((Round::Node *)object);
  }
  return false;
}

