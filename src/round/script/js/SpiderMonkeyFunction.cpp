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

static bool JSSTRING_TO_STDSTRING(JSContext *cx, JSString *jsStr, std::string *stdStr) {
  if (!jsStr)
    return false;
  
  const jschar *cval = JS_GetStringCharsZ(cx, jsStr);
  if (!cval)
    return false;
  
  *stdStr = (const char *)cval;
  
  return true;
}

void round_js_sm_setlocalnode(Round::Node *node) {
  gRoundSpiderMonkeyEngineLocalNode = node;
}

Round::Node *round_js_sm_getlocalnode() {
  return gRoundSpiderMonkeyEngineLocalNode;
}

JSBool round_js_sm_getnodegraph(JSContext *cx, unsigned argc, jsval *vp) {
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

JSBool round_js_sm_post(JSContext *cx, unsigned argc, jsval *vp) {
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


JSBool round_js_sm_setregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 2)
    return JS_FALSE;
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;

  jsval *argv = JS_ARGV(cx, vp);

  char *key, *val;
  if (!JS_ConvertArguments(cx, argc, argv, "ss", &key, &val))
    return JS_FALSE;
  
  bool isSuccess = node->setRegistry(key, val);

  JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JSBool(isSuccess)));

  return JS_TRUE;
}

JSBool round_js_sm_getregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 1)
    return JS_FALSE;
  
  jsval *argv = JS_ARGV(cx, vp);
  
  char *key;
  if (!JS_ConvertArguments(cx, argc, argv, "s", &key))
    return JS_FALSE;
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;

  std::string result;
  
  Round::Registry reg;
  if (node->getRegistry(key, &reg)) {
    Round::JSONDictionary jsonDict;
    if (reg.toJSONDictionary(&jsonDict)) {
      jsonDict.toJSONString(&result);
    }
  }

  JSString *jsResult = JS_NewStringCopyZ(cx, result.c_str());
  JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsResult));
  
  return JS_TRUE;
}
