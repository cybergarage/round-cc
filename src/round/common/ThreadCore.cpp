/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <round/common/Thread.h>

#if defined(WIN32)
#include <windows.h>
#include <time.h>
#if defined(ITRON)
#include <kernel.h>
#endif
#elif defined(BTRON)
#include <btron/proctask.h>
#include <btron/clk.h>
#include <time.h>
#elif defined(ITRON)
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#include <time.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <tk/tkernel.h>
#include <btron/proctask.h>
#include <time.h>
#else
#include <unistd.h>
#include <time.h>
#endif

#define FRACTAL_THREAD_DETACHED 1

////////////////////////////////////////////////
// ThreadCore
////////////////////////////////////////////////

#if defined(WIN32) && !defined(ITRON)
static DWORD WINAPI Win32ThreadProc(LPVOID lpParam) {
  ThreadCore *thread = (ThreadCore *)lpParam;
  thread->run();
  return 0;
}
#elif defined(BTRON) 
  static VOID BTronTaskProc(W param) {
    ThreadCore *thread = (ThreadCore *)param;
  thread->run();
  ext_tsk();
}
#elif defined(ITRON)
  static TASK ITronTaskProc(int param) {
    T_RTSK rtsk;
  if (ref_tsk(TSK_SELF, &rtsk) != E_OK)
    return;
  ThreadCore *thread = (ThreadCore *)rtsk.exinf;
  thread->run();
  exd_tsk();
}
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  static VOID TEngineTaskProc(INT stacd, VP param) {
  ThreadCore *thread = (ThreadCore *)param;
  thread->run();
  tk_exd_tsk();
}
#elif defined(TENGINE) && defined(PROCESS_BASE)
  static VOID TEngineProcessBasedTaskProc(W param) {
  ThreadCore *thread = (ThreadCore *)param;
  thread->run();
  b_ext_tsk();
}
#else
static void *PosixThreadProc(void *param) {
  Round::ThreadCore *thread = static_cast<Round::ThreadCore *>(param);
  thread->run();
  return 0;
}
#endif

////////////////////////////////////////////////
// ThreadCore
////////////////////////////////////////////////

Round::ThreadCore::ThreadCore() {
  setRunnableFlag(false);
}

bool Round::ThreadCore::start() {
  setRunnableFlag(true);
#if defined(WIN32) && !defined(ITRON)
  hThread = CreateThread(NULL, 0, Win32ThreadProc, (LPVOID)this, 0, &threadID);
#elif defined(BTRON)
  P_STATE pstate;
  prc_sts(0, &pstate, NULL);
  taskID = cre_tsk(BTronTaskProc, pstate.priority, (W)this);
  if (taskID < 0) {
    setRunnableFlag(false);
    return false;
  }
  if (wup_tsk(taskID) != 0) {
    setRunnableFlag(false);
    return false;
  }
#elif defined(ITRON)
  T_CTSK ctsk = {TA_HLNG,  (VP_INT)this, (FP)ITronTaskProc, 6, 512, NULL, NULL};
  taskID = acre_tsk(&ctsk);
  if (taskID < 0) {
    setRunnableFlag(false);
    return false;
  }
  if (sta_tsk(taskID, 0) != E_OK) {
    setRunnableFlag(false);
    del_tsk(taskID);
    return FALSE;
  }
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  T_CTSK ctsk = {(VP)this, TA_HLNG, TEngineTaskProc,10, 2048};
  taskID = tk_cre_tsk(&ctsk);
  if (taskID < E_OK) {
    setRunnableFlag(false);
    return false;
  }
  if (tk_sta_tsk(taskID, 0) < E_OK) {
    setRunnableFlag(false);
    tk_del_tsk(thread->taskID);
    return false;
  }
#elif defined(TENGINE) && defined(PROCESS_BASE)
  P_STATE pstate;
  b_prc_sts(0, &pstate, NULL);
  taskID = b_cre_tsk(TEngineProcessBasedTaskProc, pstate.priority, (W)this);
  if (taskID < 0) {
    setRunnableFlag(false);
    return false;
  }
#else
  pthread_attr_t thread_attr;
  if (pthread_attr_init(&thread_attr) != 0) {
    setRunnableFlag(false);
    return false;
  }
#if defined(FRACTAL_THREAD_DETACHED)
  if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    setRunnableFlag(false);
    pthread_attr_destroy(&thread_attr);
    return false;
  }
#endif
  if (pthread_create(&thread, &thread_attr, PosixThreadProc, this) != 0) {
    setRunnableFlag(false);
    pthread_attr_destroy(&thread_attr);
    return false;
  }
  pthread_attr_destroy(&thread_attr);
#endif
  return true;
}

Round::ThreadCore::~ThreadCore() {
  stop();
}

bool Round::ThreadCore::stop() {
  if (isRunnable() == true) {
    setRunnableFlag(false);
#if defined(WIN32) && !defined(ITRON)
    TerminateThread(hThread, 0);
    WaitForSingleObject(hThread, INFINITE);
#elif defined(BTRON)
    ter_tsk(taskID);
#elif defined(ITRON)
    ter_tsk(taskID);
    del_tsk(taskID);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
    tk_ter_tsk(taskID);
    tk_del_tsk(taskID);
#elif defined(TENGINE) && defined(PROCESS_BASE)
    b_ter_tsk(taskID);
#else
    if (pthread_cancel(thread) == 0) {
#if defined(FRACTAL_THREAD_DETACHED)
      pthread_detach(thread);
#else
      pthread_join(thread, NULL);
#endif
    }
#endif
  }
  return true;
}

void Round::ThreadCore::sleep(long mtime) {
#if defined(WIN32)
  Sleep(mtime);
#elif defined(BTRON)
  slp_tsk(mtime);
#elif defined(ITRON)
  tslp_tsk(mtime);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  tk_slp_tsk(mtime);
#elif defined(TENGINE) && defined(PROCESS_BASE)
  b_slp_tsk(mtime);
#else
  double utime = mtime * 1000.0;
  usleep((int)utime);
#endif
}

void Round::ThreadCore::setRunnableFlag(bool flag) {
  runnableFlag = flag;
}

bool Round::ThreadCore::isRunnable() {
#if !defined(WIN32) && !defined(ITRON) && !defined(BTRON) && !defined(TENGINE) && !defined(PROCESS_BASE)
  pthread_testcancel();
#endif
  return runnableFlag;
}

bool Round::ThreadCore::restart() {
  if (stop() == false)
    return false;
  return start();
}


