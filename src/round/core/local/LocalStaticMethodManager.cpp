/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/LocalNode.h>
#include <round/common/platform.h>

#include <round/core/local/method/SystemMethod.h>

Round::LocalStaticMethodManager::LocalStaticMethodManager() {
  init();
}

Round::LocalStaticMethodManager::~LocalStaticMethodManager() {
}

void Round::LocalStaticMethodManager::init() {
  addMethod(new set_method());
  addMethod(new set_route());
  addMethod(new set_timer());
  addMethod(new set_alias());
}
