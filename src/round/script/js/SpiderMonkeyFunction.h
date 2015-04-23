/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SCRIPT_JS_SM_FUNCTION_H_
#define _ROUNDCC_SCRIPT_JS_SM_FUNCTION_H_

#include <js/jsapi.h>
#include <round/core/LocalNode.h>

JSBool js_sm_getnodegraph(JSContext *cx, unsigned argc, jsval *vp);
JSBool js_sm_setregistry(JSContext *cx, unsigned argc, jsval *vp);
JSBool js_sm_getregistry(JSContext *cx, unsigned argc, jsval *vp);

void js_sm_setlocalnode(Round::Node *node);
Round::Node *js_sm_getlocalnode();

#endif
