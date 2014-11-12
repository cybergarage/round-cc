/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/Client.h>

Round::Client::Client() {
  setFinderEnabled(true);
  //this->finder.addObserver(this);
}

Round::Client::~Client() {
  Error error;
  stop(&error);
}

bool Round::Client::start(Error *error) {
  if (finderEnabled()) {
    if (!this-finder.start(error) == false)
      return false;
  }
  return true;
}

bool Round::Client::stop(Error *error) {
  if (!this-finder.stop(error) == false)
    return false;
  return true;
}

bool Round::Client::search(Error *error) {
  if (!this-finder.search(error) == false)
    return false;
  return true;
}
