/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/script/JavaScript.h>

#if defined(ROUND_SUPPORT_JS_SM)

////////////////////////////////////////////////
// Static
////////////////////////////////////////////////

static void RoundJSReportError(JSContext *cx, const char *message, JSErrorReport *report)
{
  fprintf(stderr, "%s:%u:%s\n",
          report->filename ? report->filename : "<no filename>",
          (unsigned int) report->lineno,
          message);
}

JSClass RoundJSGlobalClass = {
  "global",
  JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS | JSCLASS_HAS_PRIVATE,
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

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Round::JavaScriptEngine::init() {
  rt = JS_NewRuntime(8L * 1024L * 1024L);
  if (!rt)
    return;
  
  cx = JS_NewContext(rt, 8192);
  if (!cx)
    return;
  
  JS_SetErrorReporter(cx, RoundJSReportError);
  
  // Obsolete since JSAPI 16
  glob = JS_NewCompartmentAndGlobalObject(cx, &RoundJSGlobalClass, NULL);
  if (!glob)
    return;
    
  JS_InitStandardClasses(cx, glob);
}

////////////////////////////////////////////////
// finalize
////////////////////////////////////////////////

void Round::JavaScriptEngine::finalize() {
  JS_DestroyContext(cx);
  JS_DestroyRuntime(rt);
  JS_ShutDown();
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