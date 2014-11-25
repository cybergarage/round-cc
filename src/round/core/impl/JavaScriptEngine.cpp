/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>

#include <round/core/impl/JavaScript.h>
#include <boost/algorithm/string/replace.hpp>

Round::JavaScriptEngine::JavaScriptEngine() {
  v8::V8::InitializeICU();
  //Platform* platform = v8::platform::CreateDefaultPlatform();
  //v8::V8::InitializePlatform(platform);
  v8::V8::Initialize();
}

bool Round::JavaScriptEngine::run(Script *jsScript, const std::string &params, std::string *results, Error *error) {
  std::stringstream jsSource;
  
  jsSource << jsScript->getContent() << std::endl;
  
  std::string jsonParams = boost::algorithm::replace_all_copy(params, "\"", "\\\"");
  
  jsSource << "var jsonParams = \"" << jsonParams << "\";" << std::endl;
  jsSource << "var params = JSON.parse(jsonParams);" << std::endl;
  
  jsSource << "var results = " << jsScript->getName() << "(params);" << std::endl;
  jsSource << "var jsonResults = JSON.stringify(results);" << std::endl;
  jsSource << "jsonResults;";
  
  return run(jsSource.str(), results, error);
}

bool Round::JavaScriptEngine::run(const std::string &jsSource, std::string *results, Error *error) {

  v8::Isolate* isolate = v8::Isolate::New();
  if (!isolate) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptEngineDetailStatusInternalError);
    isolate->Dispose();
    return false;
  }
  
  v8::Isolate::Scope isolate_scope(isolate);
  
  // Create a stack-allocated handle scope.
  v8::HandleScope handle_scope(isolate);
  
  // Create a new context.
  v8::Local<v8::Context> context = v8::Context::New(isolate);
  
  // Enter the context for compiling and running the hello world script.
  v8::Context::Scope context_scope(context);
  
  // Create a string containing the JavaScript source code.
  v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, jsSource.c_str());
  if (source->Length() <= 0) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptEngineDetailStatusSourceNotFound);
    isolate->Dispose();
    return false;
  }

  // Compile the source code.
  v8::Local<v8::Script> script = v8::Script::Compile(source);
  if (script.IsEmpty()) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptEngineDetailStatusCompileError);
    isolate->Dispose();
    return false;
  }
  
  // Run the script to get the result.
  v8::Local<v8::Value> result = script->Run();
  if (result.IsEmpty()) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptEngineDetailStatusExecutionError);
    isolate->Dispose();
    return false;
  }
  
  // Convert the result to an UTF8 string and print it.
  v8::String::Utf8Value utf8(result);
  *results = *utf8;
  
  // Dispose the isolate
  isolate->Dispose();
  
  return true;
}

Round::JavaScriptEngine::~JavaScriptEngine() {
  v8::V8::Dispose();
  //v8::V8::ShutdownPlatform();
  //delete platform;
}
