/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SYSTEM_METHOD_JS_SM_FUNCTION_H_
#define _ROUNDCC_SYSTEM_METHOD_JS_SM_FUNCTION_H_

#include <js/jsapi.h>
#include <round/core/LocalNode.h>

void round_js_sm_setlocalnode(Round::Node *node);
Round::Node *round_js_sm_getlocalnode();

JSBool round_js_sm_getnodegraph(JSContext *cx, unsigned argc, jsval *vp);
JSBool round_js_sm_post(JSContext *cx, unsigned argc, jsval *vp);
JSBool round_js_sm_setregistry(JSContext *cx, unsigned argc, jsval *vp);
JSBool round_js_sm_getregistry(JSContext *cx, unsigned argc, jsval *vp);

#endif
