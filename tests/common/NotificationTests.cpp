/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

#include <round/common/Notification.h>

using namespace std;
using namespace Round;

static const int FRACTAL_NOTIFICATION_BASIC_TEST_COUNT = 100;
static int gRoundNotificationBasicCount = 0;

class BasicTestNotificationObserver : public NotificationObserver {
 public:
  BasicTestNotificationObserver() {
  
  }

  ~BasicTestNotificationObserver() {
  
  }

  bool notificationReceived(NotificationType type, void *object) {
    if (object) {
      int *intObject = (int *)object;
      *intObject += 1;
    }
    else {
      gRoundNotificationBasicCount++;
    }
    return  true;
  }
};

BOOST_AUTO_TEST_CASE(RoundNotificationBasicTest) {
  NotificationCenter notificationCenter;
  NotificationObserver *notificationObserver[FRACTAL_NOTIFICATION_BASIC_TEST_COUNT];
  NotificationObserverList notificationObserverList;

  // Initialize
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    notificationObserver[n] = new BasicTestNotificationObserver();

  // postNotification()
  gRoundNotificationBasicCount = 0;
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), 0);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK_EQUAL(notificationCenter.postNotification(), true);
  BOOST_CHECK_EQUAL(gRoundNotificationBasicCount, FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK(notificationCenter.removeAllObservers());

  // postNotification(type, obj)
  gRoundNotificationBasicCount = 0;
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), 0);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK_EQUAL(notificationCenter.postNotification(0, &gRoundNotificationBasicCount), true);
  BOOST_CHECK_EQUAL(gRoundNotificationBasicCount, FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK(notificationCenter.removeAllObservers());

  // postNotification(type, obj, err)
  notificationObserverList.clear();
  gRoundNotificationBasicCount = 0;
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), 0);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    BOOST_CHECK(notificationCenter.addObserver(notificationObserver[n]));
  BOOST_CHECK_EQUAL(notificationCenter.getObserverCount(), FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK_EQUAL(notificationCenter.postNotification(0, &gRoundNotificationBasicCount, &notificationObserverList), true);
  BOOST_CHECK_EQUAL(gRoundNotificationBasicCount, FRACTAL_NOTIFICATION_BASIC_TEST_COUNT);
  BOOST_CHECK_EQUAL(notificationObserverList.size(), 0);
  BOOST_CHECK(notificationCenter.removeAllObservers());

  // Finalize
  for (int n = 0; n < FRACTAL_NOTIFICATION_BASIC_TEST_COUNT; n++)
    delete notificationObserver[n];
}
