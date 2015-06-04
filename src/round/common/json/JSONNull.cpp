/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/common/JSON.h>

Round::JSONNull::JSONNull() {
}

bool Round::JSONNull::copy(JSONObject **newObj) const {
  JSONNull *dstObj = new JSONNull();
  return true;
}
