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

Round::LocalNativeMethodManager::LocalNativeMethodManager() {
  init();
}

Round::LocalNativeMethodManager::~LocalNativeMethodManager() {
}

void Round::LocalNativeMethodManager::init() {
  addMethod(new get_node_state());
  addMethod(new get_node_config());
  addMethod(new get_nodes());
  addMethod(new get_clusters());
  addMethod(new set_registry());
  addMethod(new get_registry());
  addMethod(new execp());
}
