/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FRACTALCC_FINDER_H_
#define _FRACTALCC_FINDER_H_

#include <round/core/impl/UPnPNodeFinder.h>

namespace Round {
  
class NodeFinder;

class Finder : public UPnPNodeFinder {
  
public:
  
  Finder();
  virtual ~Finder();

};

}

#endif
