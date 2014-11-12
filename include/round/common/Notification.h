/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_NOTIFICATION_H_
#define _FRACTALCC_NOTIFICATION_H_

#include <vector>
#include <stdlib.h>

namespace Round {
  
typedef int NotificationType;

class NotificationObserver {
  
public:
  
  NotificationObserver();  
  virtual ~NotificationObserver();

  virtual bool notificationReceived(NotificationType type, void *object) = 0;
};

class NotificationObserverList : public std::vector<NotificationObserver *> {
  
public:
  
  NotificationObserverList() {
  }
};

class NotificationCenter {
 public:
  NotificationCenter();
  ~NotificationCenter();

  bool addObserver(NotificationObserver *observer);
  bool removeObserver(NotificationObserver *observer);
  bool removeAllObservers();
  bool hasObserver(NotificationObserver *observer);
  std::size_t getObserverCount();

  bool postNotification(NotificationType type = 0, void *object = NULL, NotificationObserverList *errorObservers = NULL);

private:

  NotificationObserverList observerList;

};

}

#endif
