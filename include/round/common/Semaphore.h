/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SEMAPHORE_H_
#define _ROUNDCC_SEMAPHORE_H_

#include <time.h>

#if defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

#include <round/common/Mutex.h>

namespace Round {
#if defined(__APPLE__)

#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && (__MAC_10_6 < __MAC_OS_X_VERSION_MIN_REQUIRED)
#define FRACTAL_USE_MACOSX_DISPATCH_SEMAPHORE
typedef dispatch_semaphore_t SemaphoreId;
#else
typedef MPSemaphoreID SemaphoreId;
#endif

#else
typedef sem_t SemaphoreId;
#endif

class Semaphore {
 public:
  Semaphore(size_t count);
  ~Semaphore();

  bool post();
  bool wait(time_t timeoutSec = 0);

  void cancel();
  
private:

  SemaphoreId semId;
  bool isCanceled;
  
  Mutex semMutex;
  int semCount;
};

}

#endif
