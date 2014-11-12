/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FRACTALCC_TEST_H_
#define _FRACTALCC_TEST_H_

static const std::string FRACTAL_TEST_CLUSTER_NAME = "fractal_test";

namespace Round {

namespace Test {

const int DEFAULT_WAIT_MILLI_SECOND = 500;
const int REAL_FINDER_WAIT_MILLI_SECOND = 500;
  
int GetRandomRepeatCount(int min, int max);
void Setup();
void Sleep(long milliSecond = DEFAULT_WAIT_MILLI_SECOND);

}

}

#endif
