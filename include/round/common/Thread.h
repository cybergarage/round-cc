/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_THREAD_H_
#define _ROUNDCC_THREAD_H_

#include <vector>

#if defined(WIN32) && !defined(ITRON)
#include <windows.h>
#elif defined(BTRON)
#include <btron/proctask.h>
#elif defined(ITRON)
#if defined(WIN32) && defined(ITRON) && defined (_AFXDLL)
#include <afxwin.h>
#endif
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/proctask.h>
#else
#include <pthread.h>
#endif

namespace Round {
  
class ThreadCore {
 public:
  ThreadCore();
  virtual ~ThreadCore();

  virtual bool start();
  virtual bool stop();
  bool restart();

  bool isRunnable();
  
  void sleep(long mtime);
  
  virtual void run() = 0;


private:

  void setRunnableFlag(bool flag);

private:

#if defined(WIN32) && !defined(ITRON)
  HANDLE  hThread;
  DWORD  threadID;
#elif defined(BTRON)
  W taskID;
#elif defined(ITRON)
  ER_ID  taskID;
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  ID taskID;
#elif defined(TENGINE) && defined(PROCESS_BASE)
  WERR taskID;
#else
  pthread_t thread;
#endif

  bool runnableFlag;

};

template<typename T> class Thread : public ThreadCore {
public:
  
  Thread() {
  }
  
  virtual ~Thread() {
  }
  
  void setObject(T *object) {
    this->runObject = object;
  }

  T *getObject() {
    return this->runObject;
  }

private:

  T *runObject;
};

class ThreadList : public std::vector<ThreadCore *> {
  
public:
  
  ThreadList();
  virtual ~ThreadList();

  void addThread(ThreadCore *thread);

  bool start();
  bool stop();

  void clear();
};

class ThreadManager {
public:
  
  ThreadManager();
  virtual ~ThreadManager();

 public:
  void addThread(ThreadCore *thread);

  bool start();
  bool stop();

private:

  ThreadList threadList;
};

}

#endif
