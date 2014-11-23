/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JAVASCRIPT_H_
#define _ROUNDCC_JAVASCRIPT_H_

#include <round/core/Script.h>

namespace Round {

class ScriptGraph;

class JavaScript : public Script {

 public:
  JavaScript();
  virtual ~JavaScript();

  bool run();
  
};

}

#endif
