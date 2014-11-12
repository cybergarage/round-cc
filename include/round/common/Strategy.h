/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_STRATEGY_H_
#define _ROUNDCC_STRATEGY_H_

#include <stdlib.h>

namespace Round {
  
class Strategy {
 public:
  Strategy();
  virtual ~Strategy();

};

template<typename T> class StrategyContext {
 public:
  StrategyContext() {
    this->strategy = NULL;
  }

  virtual ~StrategyContext() {
  }

 public:
  bool hasStrategy() {
    return (this->strategy) ? true : false;
  }

  void setStrategy(T *strategy) {
    this->strategy = strategy;
  }

  T *getStrategy() {
    return this->strategy;
  }

private:

  T *strategy;
};

}

#endif
