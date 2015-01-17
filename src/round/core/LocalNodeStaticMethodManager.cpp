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

#include <round/core/method/SystemMethod.h>

Round::LocalNodeStaticMethodManager::LocalNodeStaticMethodManager() {
  init();
}

Round::LocalNodeStaticMethodManager::~LocalNodeStaticMethodManager() {
}

void Round::LocalNodeStaticMethodManager::init() {
  addMethod(new _get_node_info());
  addMethod(new _get_cluster_info());
  addMethod(new _get_network_info());
  addMethod(new _set_key());
  addMethod(new _get_key());
}
