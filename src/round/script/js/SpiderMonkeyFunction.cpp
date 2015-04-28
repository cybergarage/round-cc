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

static bool JSSTRING_TO_STDSTRING(JSContext *cx, jsval *vp, size_t argn, std::string *stdStr) {
  jsval *argv = JS_ARGV(cx, vp);
  
  jsval arg = argv[argn];
  if (!JSVAL_IS_STRING(arg))
    return false;
  
  JSString *jsStr = JSVAL_TO_STRING(arg);
  
  if (!jsStr)
    return false;

  char buffer[1024];
  size_t bufferLen = JS_EncodeStringToBuffer(jsStr, buffer, (sizeof(buffer)-1));
  buffer[bufferLen] = '\0';
  
  *stdStr = buffer;

  return true;
}

static bool JS_SET_STDSTRING_RVAL(JSContext *cx, jsval *vp, const std::string &result) {
  JSString *jsResult = JS_NewStringCopyZ(cx, result.c_str());
  JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsResult));
  return true;
}

static bool JS_SET_NODERESPONSE_RVAL(JSContext *cx, jsval *vp, Round::NodeResponse &nodeRes) {
  std::string result;
  nodeRes.getResult(&result);
  return JS_SET_STDSTRING_RVAL(cx, vp, result);
}

JSBool round_js_sm_print(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 1)
    return JS_FALSE;
  
  JS_BeginRequest(cx);
  
  std::string msg;
  JSSTRING_TO_STDSTRING(cx, vp, 0, &msg);
  
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

  JS_SET_NODERESPONSE_RVAL(cx, vp, nodeRes);
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}

JSBool round_js_sm_post_method(JSContext *cx, unsigned argc, jsval *vp) {
  if (argc < 2)
    return JS_FALSE;

  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_js_sm_getlocalnode());
  if (!node)
    return JS_FALSE;
  
  JS_BeginRequest(cx);
  
  std::string method, params, obj;
  JSSTRING_TO_STDSTRING(cx, vp, 0, &method);
  JSSTRING_TO_STDSTRING(cx, vp, 1, &params);
  if (3 <= argc) {
    JSSTRING_TO_STDSTRING(cx, vp, 2, &obj);
  }
  
  Round::Node *targetNode;
  Round::Error error;
  std::string result;
  
  if (node->findNode(obj, &targetNode, &error)) {
    targetNode->postMessage(method, params, &result);
  }
  
  JS_SET_STDSTRING_RVAL(cx, vp, result);
  
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
  
  std::string key, val;
  JSSTRING_TO_STDSTRING(cx, vp, 0, &key);
  JSSTRING_TO_STDSTRING(cx, vp, 1, &val);
  
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

  std::string key;
  JSSTRING_TO_STDSTRING(cx, vp, 0, &key);
  
  std::string result;
  
  Round::Registry reg;
  if (node->getRegistry(key, &reg)) {
    Round::JSONDictionary jsonDict;
    if (reg.toJSONDictionary(&jsonDict)) {
      jsonDict.toJSONString(&result);
    }
  }

  JS_SET_STDSTRING_RVAL(cx, vp, result);
  
  JS_EndRequest(cx);
  
  return JS_TRUE;
}
