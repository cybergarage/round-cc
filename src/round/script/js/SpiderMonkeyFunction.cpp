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
#include <round/core/local/method/SystemMethod.h>

static Round::Node *gRoundSpiderMonkeyEngineLocalNode = NULL;

void round_js_sm_setlocalnode(Round::Node *node) {
  gRoundSpiderMonkeyEngineLocalNode = node;
}

Round::Node *round_js_sm_getlocalnode() {
  return gRoundSpiderMonkeyEngineLocalNode;
}

static bool JSSTRING_TO_STDSTRING(JSContext *cx, JSString *jsStr, std::string *stdStr) {
  if (!jsStr)
    return false;

  char buffer[1024];
  size_t bufferLen = JS_EncodeStringToBuffer(jsStr, buffer, (sizeof(buffer)-1));
  buffer[bufferLen] = '\0';
  
  *stdStr = buffer;

  return true;
}

JSBool round_js_sm_print(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 1)
    return JS_FALSE;
  
  JS_BeginRequest(cx);
  
  jsval *argv = JS_ARGV(cx, vp);
  
  std::string msg;
  JSString *jsMsg = JSVAL_TO_STRING(argv[0]);
  if (jsMsg) {
    JSSTRING_TO_STDSTRING(cx, jsMsg, &msg);
  }
  
  std::cout << msg << std::endl;
  
  return JS_TRUE;
}

JSBool round_js_sm_getnodegraph(JSContext *cx, unsigned argc, jsval *vp) {
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;
  
  JS_BeginRequest(cx);
  
  Round::NodeResponse nodeRes;
  Round::SystemGetClusterInfoResponse sysRes(&nodeRes);
  sysRes.setCluster(node);

  std::string result;
  nodeRes.getResult(&result);
  
  JSString *jsResult = JS_NewStringCopyZ(cx, result.c_str());
  JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsResult));
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}

JSBool round_js_sm_post(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 3)
    return JS_FALSE;

  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;
  
  JS_BeginRequest(cx);
  
  const char *obj, *method, *params;
  if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "sss", &obj, &method, &params)) {
    JS_EndRequest(cx);
    return JS_FALSE;
  }
  
  Round::Node *targetNode;
  Round::Error error;
  std::string result;
  
  if (node->findNode(obj, &targetNode, &error)) {
    targetNode->postMessage(method, params, &result);
  }
  
  JSString *jsResult = JS_NewStringCopyZ(cx, result.c_str());
  JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsResult));
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}

JSBool round_js_sm_setregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 2)
    return JS_FALSE;
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;

  JS_BeginRequest(cx);
  
  jsval *argv = JS_ARGV(cx, vp);

  std::string key;
  JSString *jsKey = JSVAL_TO_STRING(argv[0]);
  if (jsKey) {
    JSSTRING_TO_STDSTRING(cx, jsKey, &key);
  }
  
  std::string val;
  JSString *jsVal = JSVAL_TO_STRING(argv[1]);
  if (jsVal) {
    JSSTRING_TO_STDSTRING(cx, jsVal, &val);
  }
  
  bool isSuccess = node->setRegistry(key, val);

  JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JSBool(isSuccess)));

  JS_EndRequest(cx);
  
  return JS_TRUE;
}

JSBool round_js_sm_getregistry(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 1)
    return JS_FALSE;
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;
  
  JS_BeginRequest(cx);

  jsval *argv = JS_ARGV(cx, vp);
  
  std::string key;
  JSString *jsKey = JSVAL_TO_STRING(argv[0]);
  if (jsKey) {
    JSSTRING_TO_STDSTRING(cx, jsKey, &key);
  }
  
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
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}
