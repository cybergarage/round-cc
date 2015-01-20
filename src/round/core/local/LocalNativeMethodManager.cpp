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
  addMethod(new get_node_info());
  addMethod(new get_cluster_info());
  addMethod(new get_network_info());
  addMethod(new set_key());
  addMethod(new get_key());
}
