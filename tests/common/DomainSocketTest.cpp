/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>

#include <round/common/DomainSocket.h>
#include <round/common/Thread.h>

using namespace Round;

#define TEST_DOMAIN_MESSAGE "hello"
#define TEST_DOMAIN_MESSAGE_BUF_SIZE 64
#define TEST_DOMAIN_FILE "/tmp/round_test_domain_socket"

class DomainServer : public ThreadCore {
  DomainServerSocket server;

public:
  
  DomainServer() {
  }
  
  bool open(const std::string filename) {
    return server.open(filename);
  }
  
  void run() {
    DomainSocket *sock;
    char msgBuf[TEST_DOMAIN_MESSAGE_BUF_SIZE];
    
    while (isRunnable()) {
      sock = new DomainSocket();
      if (!sock)
        continue;
      
      isRunning = true;
      
      if (server.accept(sock)) {
        delete sock;
        continue;
      }

      ssize_t msgSize = sock->recv(msgBuf, sizeof(msgBuf)-1);
      if (msgSize <= 0)
        break;

      msgBuf[msgSize] = '\0';
      message = msgBuf;
      
      delete sock;
    }
    
    if (sock) {
      delete sock;;
    }
    
    server.close();
 
    isRunning = false;
  }

public:

  bool isRunning;
  std::string filename;
  std::string message;
};

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(DomainSocketTest) {
  DomainServer server;
  DomainSocket client;

  BOOST_CHECK(server.open(TEST_DOMAIN_FILE));
  BOOST_CHECK(server.start());

  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
  
  BOOST_CHECK(client.connect(TEST_DOMAIN_FILE));
  BOOST_CHECK(client.send(TEST_DOMAIN_MESSAGE));
  BOOST_CHECK(client.close());

  while(server.isRunning) {
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
  BOOST_CHECK(server.stop());
}

BOOST_AUTO_TEST_SUITE_END()
