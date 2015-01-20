/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_FINDER_H_
#define _ROUNDCC_FINDER_H_

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
