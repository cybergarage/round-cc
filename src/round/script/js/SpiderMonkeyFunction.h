/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SCRIPT_JS_SM_H_
#define _ROUNDCC_SCRIPT_JS_SM_H_

#include <js/jsapi.h>

JSBool js_sm_get_nodegraph(JSContext *cx, unsigned argc, jsval *vp);

JSFunctionSpec JS_SM_FUNCTIONS[] = {
  JS_FN("get_nodegraph", js_sm_get_nodegraph, 0, 0),
  JS_FS_END
};

#endif
