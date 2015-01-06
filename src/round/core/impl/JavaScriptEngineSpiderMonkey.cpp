/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/core/impl/JavaScript.h>

#if defined(ROUND_USE_JS_SPIDERMONKEY)

#include <js/jsapi.h>

static JSRuntime *rt;
static JSContext *cx;
static JSObject  *glob;

////////////////////////////////////////////////
//  Static methods
////////////////////////////////////////////////

namespace Round {
  
static bool IsJavaScriptEngineListInitialized = false;

static void JavaScriptEngineExit(void) {
  JS_DestroyContext(cx);
  JS_DestroyRuntime(rt);
  JS_ShutDown();
}

static JSClass global_class = {
    "JSDGlobal",
    JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub,
    JS_PropertyStub,
    JS_PropertyStub,
    JS_StrictPropertyStub,
    JS_EnumerateStub,
    JS_ResolveStub,
    JS_ConvertStub,
    JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
  };
}

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Round::JavaScriptEngine::init() {
  if (!IsJavaScriptEngineListInitialized) {
    rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (!rt)
      return;
    cx = JS_NewContext(rt, 8192);
    if (!cx)
      return;
    glob = JS_NewGlobalObject(cx, &global_class);
    if (!glob)
      return;
    JS_InitStandardClasses(cx, glob);
    atexit(JavaScriptEngineExit);
  }
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::JavaScriptEngine::run(const std::string &jsSource, std::string *results, Error *error) const {
  if (!rt || !cx || !glob)
    return false;
  
  jsval rval;
  JSBool ok = JS_EvaluateScript(cx, glob, jsSource.c_str(), (uintN)jsSource.length(), "", 0, &rval);
  
  if (ok) {
    JSString *rstr = JS_ValueToString(cx, rval);
    if (rstr) {
      *results = JS_EncodeString(cx, rstr);
    }
  }
  
  return ok;
}

#endif
