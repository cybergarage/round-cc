/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CONSOLEERROR_H_
#define _ROUNDCC_CONSOLEERROR_H_

#include <round/common/Error.h>

namespace Round {

class ConsoleError : public Error {

private:

public:
  
  ConsoleError();
  ~ConsoleError();
  
  bool isSQLCommand();

  void clear();
};

}

#endif
