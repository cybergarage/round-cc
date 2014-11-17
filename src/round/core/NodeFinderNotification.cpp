/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/NodeFinder.h>

Round::NodeFinderNotification::NodeFinderNotification() {
}

Round::NodeFinderNotification::~NodeFinderNotification() {
}

bool Round::NodeFinderNotification::postNodeAdded(Round::Node *node, NotificationObserverList *errorObservers) {
  return Round::NotificationCenter::postNotification(NodeFinderObserverTypeAdd, node, errorObservers);
}

bool Round::NodeFinderNotification::postNodeRemoved(Round::Node *node, NotificationObserverList *errorObservers) {
  return Round::NotificationCenter::postNotification(NodeFinderObserverTypeRemove, node, errorObservers);
}
