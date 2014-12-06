/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <stdio.h>
#include <time.h>

#include <round/common/Message.h>

using namespace std;
using namespace Round;

#define FRACTAL_MESSAGE_BASIC_TEST_COUNT 10

BOOST_AUTO_TEST_CASE(RoundMessageManagerTest) {
  MessageManager msgMgr;

  char key[32], value[32];
  for (int n = 0; n < FRACTAL_MESSAGE_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    snprintf(value, sizeof(value), "%d", n);
    Message *msg = new Message();
    msg->set(key, value);
    BOOST_CHECK(msgMgr.pushMessage(msg));
  }

  for (int n = 0; n < FRACTAL_MESSAGE_BASIC_TEST_COUNT; n++) {
    snprintf(key, sizeof(key), "key%d", n);
    snprintf(value, sizeof(value), "%d", n);
    const Message *msg;
    BOOST_CHECK(msgMgr.waitMessage(&msg));
    string value;
    BOOST_CHECK(msg->get(key, &value));
    BOOST_CHECK_EQUAL(value.compare(value), 0);
    delete msg;
  }
}
