/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_H_
#define _ROUNDCC_SCRIPT_H_

#include <string>
#include <map>

#include <round/common/Error.h>

namespace Round {

class Script {

 public:
  Script();
  virtual ~Script();

  bool setName(const std::string &name) {
    this->name = name;
    return true;
  }
  
  const std::string &getName() const {
    return this->name;
  }
  
  const bool hasName() const {
    return (0 < this->name.length()) ? true : false;
  }
  
  bool setContent(const std::string &content) {
    this->content = content;
    return true;
  }
  
  const std::string &getContent() const {
    return this->content;
  }
  
  virtual bool run(const std::string &params, std::string *results, Error *error) = 0;

 private:
  std::string name;
  std::string content;
};

class ScriptMap : public std::map<std::string, Script *> {
    
public:
    
  ScriptMap();
  virtual ~ScriptMap();
  bool hasScript(const std::string &name);
  Script *getScript(const std::string &name);

  void clear();
};

enum JavaScriptEngineStatus {
  ScriptEngineStatusOk          = 200,
  ScriptEngineStatusBadRequest  = 400,
};

enum JavaScriptEngineDetailStatus {
  ScriptEngineDetailStatusOk              = 0,
  ScriptEngineDetailStatusParserError     = -32700,
  ScriptEngineDetailStatusInvalidRequest  = -32600,
  ScriptEngineDetailStatusMethodNotFound  = -32601,
  ScriptEngineDetailStatusInvalidParams   = -32602,
  ScriptEngineDetailStatusInternalError   = -32603,
  ScriptEngineDetailStatusSourceNotFound  = -32000,
  ScriptEngineDetailStatusCompileError    = -32001,
  ScriptEngineDetailStatusExecutionError  = -32002,
};
  
class ScriptEngine {
    
public:
  ScriptEngine();
  virtual ~ScriptEngine();

  bool setScript(Script *script);
  bool hasScript(const std::string &name);
  
  bool run(const std::string &name, const std::string &params, std::string *results, Error *error);
  
  virtual bool run(Script *script, const std::string &params, std::string *results, Error *error) = 0;

private:
  
  ScriptMap scripts;
};

}

#endif
