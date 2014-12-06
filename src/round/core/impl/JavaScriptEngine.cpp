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
#include <boost/algorithm/string/replace.hpp>

#include <round/core/Log.h>
#include <round/core/impl/JavaScript.h>

Round::JavaScriptEngine::JavaScriptEngine() : ScriptEngine(JavaScript::LANGUAGE) {
  v8::V8::InitializeICU();
#if defined(ROUND_V8_USE_LIBPLATFORM)
  this->platform = v8::platform::CreateDefaultPlatform();
  v8::V8::InitializePlatform(this->platform);
#endif
  v8::V8::Initialize();

  this->isolate = v8::Isolate::New();
}

bool Round::JavaScriptEngine::run(const Script *jsScript, const ScriptParams &params, ScriptResults *results, Error *error) const {
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

bool Round::JavaScriptEngine::run(const std::string &jsSource, std::string *results, Error *error) const {

  RoundLogTrace("%s", jsSource.c_str());
  
  if (!this->isolate) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptManagerErrorCodeInternalError);
    return false;
  }
  
  // Make this isolate the current one.
  v8::Isolate::Scope isolate_scope(this->isolate);
  
  // Create a stack-allocated handle scope.
  v8::HandleScope handle_scope(this->isolate);
  
  // Create a new context.
  v8::Local<v8::Context> context = v8::Context::New(this->isolate);
  
  // Enter the context for compiling and running the hello world script.
  v8::Context::Scope context_scope(context);
  
  // Create a string containing the JavaScript source code.
  v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, jsSource.c_str());
  if (source->Length() <= 0) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptManagerErrorCodeSourceNotFound);
    return false;
  }

  // Compile the source code.
  v8::Local<v8::Script> script = v8::Script::Compile(source);
  if (script.IsEmpty()) {
    error->setCode(ScriptEngineStatusBadRequest);
    error->setCode(ScriptManagerErrorCodeCompileError);
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

  RoundLogTrace("%s", results->c_str());
  
  return true;
}

Round::JavaScriptEngine::~JavaScriptEngine() {
  // Dispose the isolate
  if (this->isolate)
    isolate->Dispose();
  
  v8::V8::Dispose();
#if defined(ROUND_V8_USE_LIBPLATFORM)
  v8::V8::ShutdownPlatform();
  delete platform;
#endif
}
