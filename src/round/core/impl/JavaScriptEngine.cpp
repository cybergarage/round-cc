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

Round::JavaScriptEngine::JavaScriptEngine() {
  v8::V8::InitializeICU();
  //Platform* platform = v8::platform::CreateDefaultPlatform();
  //v8::V8::InitializePlatform(platform);
  v8::V8::Initialize();
}

bool Round::JavaScriptEngine::run(Script *jscript, const std::string &params, std::string *results, Error *error) {
  v8::Isolate* isolate = v8::Isolate::New();
  
  v8::Isolate::Scope isolate_scope(isolate);
  
  // Create a stack-allocated handle scope.
  v8::HandleScope handle_scope(isolate);
  
  // Create a new context.
  v8::Local<v8::Context> context = v8::Context::New(isolate);
  
  // Enter the context for compiling and running the hello world script.
  v8::Context::Scope context_scope(context);
  
  // Create a string containing the JavaScript source code.
  v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, "var jsontext = '{\"firstname\":\"Satoshi\"}';var contact = JSON.parse(jsontext);\njsontext;\ncontact;\nvar jsonstring = JSON.stringify(contact);jsonstring;");
  
  // Compile the source code.
  v8::Local<v8::Script> script = v8::Script::Compile(source);
  
  // Run the script to get the result.
  v8::Local<v8::Value> result = script->Run();
  
  // Convert the result to an UTF8 string and print it.
  v8::String::Utf8Value utf8(result);
  printf("%s\n", *utf8);
  
  return true;
}

Round::JavaScriptEngine::~JavaScriptEngine() {
  v8::V8::Dispose();
  //v8::V8::ShutdownPlatform();
  //delete platform;
}
