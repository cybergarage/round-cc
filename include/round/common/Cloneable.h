/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_CLONEABLE_H_
#define _FRACTALCC_CLONEABLE_H_

namespace Round {

template<typename T> class Cloneable {

public:
  
  virtual bool isCloneable() const = 0;

  virtual T *clone() const {
    return NULL;
  }
};

}

#endif
