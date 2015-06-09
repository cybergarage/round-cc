/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/Client.h>

Round::Client::Client() {
  setFinderEnabled(true);
  this->finder.addObserver(this);
}

Round::Client::~Client() {
  Error error;
  stop(&error);
}

bool Round::Client::start(Error *error) {
  if (finderEnabled()) {
    if (!this->finder.start(error))
      return false;
  }
  return true;
}

bool Round::Client::stop(Error *error) {
  if (finderEnabled()) {
    if (!this->finder.stop(error))
      return false;
  }
  return true;
}

bool Round::Client::search(Error *error) {
  if (finderEnabled()) {
    if (!this->finder.search(error))
      return false;
  }
  return true;
}
