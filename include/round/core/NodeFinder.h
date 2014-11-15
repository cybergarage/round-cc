/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_NODEFINDER_H_
#define _ROUNDCC_NODEFINDER_H_

#include <round/common/Notification.h>
#include <round/core/ErrorNo.h>

namespace Round {

enum {
NodeFinderObserverTypeNode = 0,
NodeFinderObserverTypeAdd,
NodeFinderObserverTypeRemove
};

class Node;

class NodeFinderObserver : public NotificationObserver {
  
public:
  
  NodeFinderObserver();
  ~NodeFinderObserver();
  
 public:
  virtual bool nodeAdded(Node *node) = 0;
  virtual bool nodeRemoved(Node *node) = 0;

private:

  bool notificationReceived(NotificationType type, void *object);
};

class NodeFinderNotification : public NotificationCenter {
public:
  
  NodeFinderNotification();
  ~NodeFinderNotification();

  bool postNodeAdded(Node *node, NotificationObserverList *errorObservers = NULL);
  bool postNodeRemoved(Node *node, NotificationObserverList *errorObservers = NULL);
};

class NodeFinder {
 public:
  NodeFinder();
  virtual ~NodeFinder();

  virtual bool start(Error *error) = 0;
  virtual bool stop(Error *error) = 0;
  virtual bool search(Error *error) = 0;

public:

  bool addObserver(NodeFinderObserver *observer) {
    return this->notification.addObserver(observer);
  }

  bool removeObserver(NodeFinderObserver *observer) {
    return this->notification.removeObserver(observer);
  }
  
  std::size_t getObserverCount() {
    return this->notification.getObserverCount();
  }

  bool postNodeAdded(Node *node, NotificationObserverList *errorObservers = NULL) {
    return this->notification.postNodeAdded(node, errorObservers);
  }

  bool postNodeRemoved(Node *node, NotificationObserverList *errorObservers = NULL) {
    return this->notification.postNodeRemoved(node, errorObservers);
  }

private:

  NodeFinderNotification notification;

};

class NodeFinderList : public std::vector<NodeFinder *> {
public:
  
  NodeFinderList();
  virtual ~NodeFinderList();
  
};

}

#endif
