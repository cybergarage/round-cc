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

#if defined(ROUND_SUPPORT_JS_V8)

#include <stdlib.h>

#include <v8.h>
#if defined(ROUND_V8_USE_LIBPLATFORM)
#include "libplatform/libplatform.h"
#endif

#include <round/core/Log.h>

////////////////////////////////////////////////
//  Static methods
////////////////////////////////////////////////

namespace Round {

static bool IsJavaScriptEngineListInitialized = false;
#if defined(ROUND_V8_USE_LIBPLATFORM)
static v8::Platform *JavaScriptEnginePlatform;
#endif

static void JavaScriptEngineExit(void) {
  v8::V8::Dispose();
#if defined(ROUND_V8_USE_LIBPLATFORM)
  v8::V8::ShutdownPlatform();
  delete JavaScriptEnginePlatform;
#endif
}

}

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Round::JavaScriptEngine::init() {
  if (!IsJavaScriptEngineListInitialized) {
    v8::V8::Initialize();
#if defined(ROUND_V8_USE_LIBPLATFORM)
    JavaScriptEnginePlatform = v8::platform::CreateDefaultPlatform();
    v8::V8::InitializePlatform(JavaScriptEnginePlatform);
#endif
    v8::V8::Initialize();
    IsJavaScriptEngineListInitialized = true;
    atexit(JavaScriptEngineExit);
  }
}

////////////////////////////////////////////////
// finalize
////////////////////////////////////////////////

void Round::JavaScriptEngine::finalize() {
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::JavaScriptEngine::run(const std::string &jsSource, std::string *results, Error *error) const {

  RoundLogTrace("%s", jsSource.c_str());
  
  // Create a new Isolate and make it the current one.
  v8::Isolate *isolate = v8::Isolate::New();
  if (!isolate) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setDetailCode(RPC::JSON::ErrorCodeInternalError);
    return false;
  }

  // Create new scope
  {
    // Make this isolate the current one.
    v8::Isolate::Scope isolate_scope(isolate);
  
    // Create a stack-allocated handle scope.
    v8::HandleScope handle_scope(isolate);
  
    // Create a new context.
    v8::Local<v8::Context> context = v8::Context::New(isolate);
  
    // Enter the context for compiling and running the the script.
    v8::Context::Scope context_scope(context);
  
    // Create a string containing the JavaScript source code.
    v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, jsSource.c_str());
    if (source->Length() <= 0) {
      error->setCode(ScriptEngineStatusBadRequest);
      error->setDetailCode(RPC::JSON::ErrorCodeScriptCompileError);
      return false;
    }

    // Compile the source code.
    v8::Local<v8::Script> script = v8::Script::Compile(source);
    if (script.IsEmpty()) {
      error->setCode(ScriptEngineStatusBadRequest);
      error->setDetailCode(RPC::JSON::ErrorCodeScriptCompileError);
      return false;
    }
  
    // Run the script to get the result.
    v8::Local<v8::Value> result = script->Run();
    if (!result.IsEmpty()) {
      // Convert the result to an UTF8 string
      v8::String::Utf8Value utf8(result);
      *results = *utf8;
    }
    else {
      *results = "";
    }
  }

  // Dispose the isolate
  isolate->Dispose();

  RoundLogTrace("%s", results->c_str());
  
  return true;
}

#endif

