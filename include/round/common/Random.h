/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_RANDOM_H_
#define _ROUNDCC_RANDOM_H_

namespace Round {

class Random {
 public:
  Random();
  Random(unsigned int min, unsigned int max);
  ~Random();

  unsigned int rand();

private:

  void initialize(unsigned int min, unsigned int max);
  int minRange;
  int maxRange;

};

}

#endif
