/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <round/common/Notification.h>

Round::NotificationCenter::NotificationCenter() {
}

Round::NotificationCenter::~NotificationCenter() {
}

bool Round::NotificationCenter::hasObserver(NotificationObserver *targetObserver) {
  for (NotificationObserverList::iterator observer = observerList.begin(); observer != observerList.end(); observer++) {
    if ((*observer) == targetObserver)
      return true;
  }
  return false;
}

bool Round::NotificationCenter::addObserver(NotificationObserver *observer) {
  if (hasObserver(observer))
    return true;
  observerList.push_back(observer);
  return true;
}

bool Round::NotificationCenter::removeObserver(NotificationObserver *targetObserver) {
  for (NotificationObserverList::iterator observer = observerList.begin(); observer != observerList.end(); observer++) {
    if ((*observer) == targetObserver) {
      observerList.erase(observer);
      return true;
    }
  }
  return false;
}

bool Round::NotificationCenter::removeAllObservers() {
  while (0 < this->observerList.size()) {
    NotificationObserver *observer = this->observerList.at(0);
    removeObserver(observer);
  }
  return true;
}

std::size_t Round::NotificationCenter::getObserverCount() {
  return observerList.size();
}

bool Round::NotificationCenter::postNotification(NotificationType type, void *object, NotificationObserverList *errorObservers) {
  bool isAllSuccess = true;

  for (NotificationObserverList::iterator observer = observerList.begin(); observer != observerList.end(); observer++) {
    if ((*observer)->notificationReceived(type, object) == false) {
      isAllSuccess = false;
      if (errorObservers)
        errorObservers->push_back((*observer));
    }
  }

  return isAllSuccess;
}
