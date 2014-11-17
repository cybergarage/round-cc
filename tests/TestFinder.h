/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SIMPLENODEFINDER_H_
#define _ROUNDCC_SIMPLENODEFINDER_H_

#include <round/Round.h>

class TestNodeFinder : public Round::NodeFinder {
 public:
  TestNodeFinder() {
  }

  bool start(Round::Error *err) {return true;}
  bool stop(Round::Error *err) {return true;}
  bool search(Round::Error *err) {return true;}
};

#endif

