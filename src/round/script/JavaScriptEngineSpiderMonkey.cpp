/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <round/script/JavaScript.h>
#include <round/script/js/SpiderMonkeyFunction.h>

#if defined(ROUND_SUPPORT_JS_SM)

////////////////////////////////////////////////
// Static
////////////////////////////////////////////////

static JSFunctionSpec JS_SM_FUNCTIONS[] = {
  JS_FN(ROUNDCC_SCRIPT_PRINT_METHOD, round_js_sm_print, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_GET_NETWORK_STATE, round_js_sm_getnetworkstate, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_GET_CLUSTER_STATE, round_js_sm_getclusterstate, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_GET_NODE_STATE, round_js_sm_getnodestate, 0, 0),
  JS_FN(ROUNDCC_SCRIPT_POST_METHOD, round_js_sm_postmethod, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_SET_REGISTRY, round_js_sm_setregistry, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_GET_REGISTRY, round_js_sm_getregistry, 0, 0),
  JS_FN(ROUNDCC_SYSTEM_METHOD_REMOVE_REGISTRY, round_js_sm_removeregistry, 0, 0),
  JS_FS_END
};

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
  JS_SetCStringsAreUTF8();
  
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
  JS_DefineFunctions(cx, glob, JS_SM_FUNCTIONS);
  
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

  lock();
  
  round_js_sm_setlocalnode(hasNode() ? getNode() : NULL);
  
  jsval rval;
  JSBool ok = JS_EvaluateScript(cx, glob, jsSource.c_str(), (uintN)jsSource.length(), "", 0, &rval);
  
  if (ok) {
    JSString *rstr = JS_ValueToString(cx, rval);
    if (rstr) {
      *results = JS_EncodeString(cx, rstr);
    }
  }
  
  round_js_sm_setlocalnode(NULL);
  
  unlock();
  
  return ok;
}

#endif
