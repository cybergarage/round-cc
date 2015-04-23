/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/script/js/SpiderMonkeyFunction.h>

static Round::Node *gRoundSpiderMonkeyEngineLocalNode = NULL;

void js_sm_setlocalnode(Round::Node *node) {
  gRoundSpiderMonkeyEngineLocalNode = node;
}

Round::Node *js_sm_getlocalnode() {
  return gRoundSpiderMonkeyEngineLocalNode;
}

JSBool js_sm_getnodegraph(JSContext *cx, unsigned argc, jsval *vp) {
  JS_ASSERT(argc == 1);
  jsval *argv = JS_ARGV(cx, vp);
  JS_ASSERT(JSVAL_IS_STRING(argv[0]));
  JSString *str = JSVAL_TO_STRING(argv[0]);
  /*
  const jschar *chars = str->getChars(cx);
  JS_ASSERT(chars);
  size_t len = str->length();
  return callbackData->evalVersion(chars, len, JSVERSION_1_6);
  */
  
  return JS_TRUE;
}

JSBool js_sm_post(JSContext *cx, unsigned argc, jsval *vp) {
  JS_BeginRequest(cx);
  
  //JSObject* myObject = JS_NewObject(context, &myClass, NULL, NULL);
  //*vp = OBJECT_TO_JSVAL(myObject);
  
  
  /*
  bool
  JS_CallFunctionName(JSContext *cx, JSObject *obj, const char *name, unsigned argc, 
   jsval *argv, jsval *rval);
  */

  /*
  jsvalRoot rval(cx);
  CHECK(JS_CallFunctionName(cx, global, "main", 0, NULL, rval.addr()));
  CHECK_SAME(rval, INT_TO_JSVAL(123));
   */
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}


JSBool js_sm_setregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 2)
    return JS_FALSE;
  
  Round::LocalNode *localNode = js_sm_getlocalnode();
  if (!localNode)
    return FALSE;
  
  jsval *argv = JS_ARGV(cx, vp);
  JSString *key = JSVAL_TO_STRING(argv[0]);
  JSString *val = JSVAL_TO_STRING(argv[1]);
  
  return JS_TRUE;
}

JSBool js_sm_getregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 1)
    return JS_FALSE;
  
  jsval *argv = JS_ARGV(cx, vp);
  JSString *key = JSVAL_TO_STRING(argv[0]);

  return JS_TRUE;
}
